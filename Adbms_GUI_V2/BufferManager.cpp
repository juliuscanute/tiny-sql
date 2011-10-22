
#include "BufferManager.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

frame_header h;
db_index dbi[MAX_DB];
struct p_que* pq;
BUF_POOL *lru,*mru;
struct free_frames* ff;

//priority* pr[NUM_FRAMES];


    bool buffer::buf_init()
     {
        int i;
        //Frame Size
          h.frame_size = sizeof(BUF_POOL)-1+sizeof(char)*PAGE_SIZE;

          //Create Memory for Buffer Pool
          buf_pool = (BUF_POOL*)malloc(NUM_FRAMES*h.frame_size);

          //Initialize Frame Header, Priority Que
          pq=(struct p_que*)malloc(sizeof(struct p_que)*NUM_FRAMES);
          ff=(struct free_frames*)malloc(sizeof(struct free_frames)*NUM_FRAMES);
          cout<<"malloced"<<endl;
          h.free_frames=NUM_FRAMES;


          cout<<"initializing variables"<<endl;
          for(i=0;i<NUM_FRAMES;i++)
          {
              (pq+i)->bid=-1;
              (pq+i)->lru=false;
              (pq+i)->page=buf_pool+i;
              (ff+i)->frame=buf_pool+i;
              if(i<NUM_FRAMES-1)
              {
                  ff[i].next=&ff[i+1];
                  pq[i].next=&pq[i+1];
              }
          }


          cout<<"Initializing priority Queue and free frame list"<<endl;
          pq[0].prev=&pq[NUM_FRAMES-1];
          pq[NUM_FRAMES-1].next=&pq[0];
          h.first_free_frame=&ff[0];
          h.last_free_frame=&ff[NUM_FRAMES-1];
          h.dbs_open =0;
          cout<<"Initializing db.index"<<endl;


          for(int i=0;i<MAX_DB;i++)
              dbi[i].bid=-1;
          cout<<"Initialization done.. returning to main.."<<endl;
//          buffer::test_buffer();
        return true;
     }

    void buffer::test_buffer()
    {
        for(int i=0;i<MAX_DB;i++)
        {
            cout<<"Printing Index:"<<i<<endl;
            cout<<dbi[i].bid<<endl;
        }
    }

    bool buffer::createDB(char* dbname, int numPages)
     {
        char* db_name;
        int bid;
        BUF_POOL* page=(BUF_POOL*)malloc(sizeof(BUF_POOL));
        page->_dirty = -1;
        db_name = buffer::addExt(dbname);
        buffer::test_buffer();
       if(fopen(db_name,"rb")!=NULL)
        {
         return true;
        }
        bid=open(db_name,O_CREAT,0777);
        if(bid>=0)
         {
            for(int i=0;i<numPages;i++)
            {
                page->_pageno=i;
                write(bid,page,sizeof(BUF_POOL));
            }

            lseek(bid,NUM_FRAMES*h.frame_size,SEEK_SET);
          close(bid);
          return true;
        }
        return false;

     }

    long buffer::openDB(char* dbname)
     {

        int i, bid;
        char* db_name = buffer::addExt(dbname);


        bid=open(db_name,O_RDWR);
        if(bid>=0)
        {
            cout<<"Db file opened.."<<endl;
            for(i=0;i<MAX_DB;i++)
             {
                if(!strcmp(dbi[i].db,db_name)&&dbi[i].bid>0)
                {
                    cout<<"Database is already open at index.."<<i<<endl;
                    return dbi[i].bid;
                }
             }
            for(i=0;i<MAX_DB;i++)
             {
                if(dbi[i].bid==-1)
                {
                    cout<<"Assigning Index.."<<i<<endl;
                    dbi[i].bid=bid;
                    strcpy(dbi[i].db,db_name);
                    h.dbs_open++;
                return bid;
                }
             }
            if(h.dbs_open==MAX_DB)
              cout<<"There are several other databases open, please close some of those to open new database"<<endl;
        }
        cout<<"Error in Opening Database.."<<endl;
        return -1;
    }


    bool buffer::closeDB(char* dbname)
     {
        int i,j,fd,count,pgNum;
        char* db_name = buffer::addExt(dbname);

        for(i=0;i<MAX_DB;i++)
        {
            if(!strcmp(dbi[i].db,db_name))
            {
                cout<<"Fd:"<<i<<endl;
                struct p_que* temp;
                temp=h.mru;
                count=0;
                for(j=NUM_FRAMES-h.free_frames;j>0;j--)
                {
                    cout<<"Database open at index:"<<i<<endl;
                    if(pq->bid==-1)
                        continue;
                    if(/*dbi[i].bid==temp->bid&&*/temp->page->_dirty==1)
                    {
                        cout<<"Writing the pageNumber:"<<j<<endl;
                        temp->page->_dirty = 0;
                        count++;
                        pgNum = temp->page->_pageno;
                        buffer::writeIntoDB(fd,&buf_pool[j],pgNum);
                        temp->bid=-1;
                    }
                }
                close(dbi[i].bid);
                dbi[i].bid = -1;
                h.free_frames+=count;
                return true;
            }
        }
        cout<<"Database '"<<dbname<<"' is not open"<<endl;
        return false;
     }


    bool buffer::deleteDB(char* dbname)
     {
        char* db_name = buffer::addExt(dbname);
        if(open(db_name,O_RDONLY)>0)
        {
            for(int i=0;i<MAX_DB;i++)
             {
              if(!strcmp(dbi[i].db,db_name))
              {
                  cout<<"Cannot delete "<<dbname<<"...  It is being used"<<endl;
                  return false;
              }
             }
            remove(db_name);
            return true;
        }
        cout<<dbname<<" doesn't exist"<<endl;
        return false;
     }


    bool buffer::readFromDB(int bid, BUF_POOL* buf, int pageNumber)
     {
        int i,lru;
        for(i=0;i<MAX_DB;i++)
        {
            if(dbi[i].bid==bid)
            {
                lseek(bid,pageNumber*h.frame_size,SEEK_SET);
                read(bid,buf,h.frame_size);

//                for(i=0;i<NUM_FRAMES;i++)
//                {
//                    if(h.first_free_frame==NUM_FRAMES)
//                    {
//                        lru = h.priority[0];
//                        if(buf_pool[lru]._dirty>0)
//                            buffer::writeIntoDB(bid,&buf_pool[lru],buf_pool[lru]._pageno);
//                        //buf_pool[lru]=buf;
//                        h.priority[0]=NUM_FRAMES;
//                        buffer::sort();
//                        return true;
//                    }
//                    //buf_pool[h.first_free_frame]=buf;
//                    for(h.first_free_frame=0;h.first_free_frame<NUM_FRAMES;h.first_free_frame++)
//                    {
//                        if(buf_pool[h.first_free_frame]._dirty==-1)
//                            break;
//                    }
//                    return true;

//                }
                return false;
            }
        }
     }

    bool buffer::writeIntoDB(int fd,BUF_POOL* buffer,int pageNumber)
    {
        int i;
        cout<<"Checking index.."<<fd<<endl;
        for(i=0;i<MAX_DB;i++)
        {
            if(dbi[i].bid==fd)
            {
                cout<<"writing page into the file.."<<fd<<endl;
                lseek(fd,pageNumber*h.frame_size,SEEK_SET);
                write(fd,buffer,h.frame_size);
                return true;
            }
        }
        cout<<"Database is not open or page not found"<<endl;
        return false;

    }

    BUF_POOL* buffer::ReadPage(int fd,int PageNumber)
    {
        p_que* temp;
        cout<<"Looking for the page in the buffer pool"<<endl;

        //Search for the requested page in the Buffer Pool
        if(h.free_frames!=NUM_FRAMES)
        {
            temp=h.mru;
        do
        {
            if(temp->bid==fd&&temp->page->_pageno==PageNumber)
            {
                temp->prev->next=temp->next;
                temp->next->prev=temp->prev;
                temp->prev=h.mru;
                h.mru->next=temp;
                h.mru=h.mru->next;
                if(temp->lru)
                {
                    temp->lru=false;
                    h.lru=h.lru->next;
                    h.lru->lru=true;
                }
                return temp->page;
            }
            temp=temp->prev;
        }
        while(!temp->lru);
    }

        cout<<"not found.."<<endl<<"fetching from database.."<<endl;
        if(h.free_frames>0)
        {
            buffer::readFromDB(fd,h.first_free_frame->frame,PageNumber);
            if(h.lru==NULL)
            {
                h.lru=pq+0;
                h.mru=pq+0;
                h.lru->next=h.mru;
                h.mru->prev=h.lru;
            }
            else
            {
                h.mru->next=h.first_free_frame->p;
                h.mru=h.mru->next;
                h.mru->next=h.lru;
                if(--h.free_frames>0)
                h.first_free_frame=h.first_free_frame->next;

            }
            return h.mru->page;
        }


        cout<<"No Free Frames.."<<endl<<"replacing least recently used.."<<endl;
        if(h.lru->page->_dirty&&h.lru->bid>-1)
        {
            buffer::writeIntoDB(fd,h.lru->page,PageNumber);
        }
        if(buffer::readFromDB(fd,h.lru->page,PageNumber)!=true)
        {
            h.mru->next=h.lru;
            h.lru->prev=h.mru;
            h.mru=h.mru->next;
            h.lru=h.lru->next;
        }
      return h.mru->page;

    }


    char* buffer::addExt(char* dbname)
     {
       char* name = (char*)malloc(MAX_FILE_NAME);
       strcpy(name,dbname);
       strcat(name,".db");
       cout<<name<<endl;
       return name;
     }





