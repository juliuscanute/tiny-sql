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

//priority* pr[NUM_FRAMES];


    bool buffer::buf_init()
     {
        int i;
          h.frame_size = sizeof(BUF_POOL)-1+sizeof(char)*PAGE_SIZE;
          buf_pool = (BUF_POOL*)malloc(NUM_FRAMES*h.frame_size);
          pq=(struct p_que*)malloc(sizeof(struct p_que)*NUM_FRAMES);
          h.free_frames=NUM_FRAMES;


          for(i=0;i<NUM_FRAMES;i++)
              pq[i].bid=-1;


          h.first_free_frame = 0;
          h.dbs_open =0;


          for(int i=0;i<MAX_DB;i++)
              dbi[i].bid=-1;
          buffer::test_buffer();
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

    bool buffer::ReadPage(int fd,BUF_POOL* page,int PageNumber)
    {
        int i=NUM_FRAMES-h.free_frames;

        cout<<"Looking into the buffer_pool for the requested page"<<endl;
//       page = (BUF_POOL*)malloc(sizeof(BUF_POOL));

        p_que* temp;
        if(h.free_frames<NUM_FRAMES)
        {
            temp=h.mru;
            if(temp->bid==fd&&temp->page->_pageno==PageNumber)
            {
                page=temp->page;
                return true;
            }
            while(i>0)
            {
                temp=temp->prev;
                if(temp->bid==fd&&temp->page->_pageno==PageNumber)
                {
                    cout<<"Page Found"<<endl;
                    page=temp->page;
                    temp->prev->next=temp->next;
                    h.mru->next =temp;
                    h.mru =h.mru->next;
                    h.mru->next=NULL;
                    return true;
                }
                i--;
            }
        }

        cout<<"Page not found in Buffer.. loading from db"<<endl;
        page=(BUF_POOL*)malloc(sizeof(BUF_POOL));
        if(buffer::readFromDB(fd,page,PageNumber)==true&&page!=NULL)
        {
            cout<<"Success.. Page Found"<<endl<<"Adding page to the buffer pool.."<<endl;

            if(h.free_frames>0)
            {
                for(i=0;i<NUM_FRAMES;i++)
                {
                    if(pq[i].bid==-1)
                    {
                        memmove(&buf_pool[i],page,sizeof(BUF_POOL));
                        free(page);
                        buf_pool[i]._dirty=0;
                        pq[i].page=&buf_pool[i];
                        pq[i].bid=fd;
                        if(h.lru==NULL)
                        {
                            h.mru =&pq[i];
                            h.lru=&pq[i];
                            h.lru->next=h.mru;
                            h.mru->prev=h.lru;
                        }
                        else
                        {
                            h.mru->next=&pq[i];
                            h.mru=h.mru->next;
                        }
                        h.free_frames--;
                        return true;
                    }
                }
            }

            else
            {
                    if(h.lru->page->_dirty)
                    {
                        if(buffer::writeIntoDB(fd,h.lru->page,h.lru->page->_pageno)!=true)
                        {
                            cout<<"Failed to write into db, while replacing the page.."<<endl;
                            return false;
                        }
                    }
                    memmove(h.lru->page,page,sizeof(BUF_POOL));
                    free(page);
                    h.mru->next=h.lru;
                    h.mru=h.mru->next;
                    h.lru=h.lru->next;
            }

             return true;
        }
        else
        {
            cout<<"Page Not Found"<<endl;
            return true;
        }

    }


    char* buffer::addExt(char* dbname)
     {
       char* name = (char*)malloc(MAX_FILE_NAME);
       strcpy(name,dbname);
       strcat(name,".db");
       cout<<name<<endl;
       return name;
     }





