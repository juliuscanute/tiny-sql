#include "database.h"
#include "bufferManager.h"

#include <malloc.h>
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

BUF_POOL* buf_pool[num_frames];
int free_frames = num_frames;
int priority[num_frames];
long frame_size = sizeof(BUF_POOL)-1+sizeof(char)*p_size;

bool buffer_init()
{

    for(int i=0;i<num_frames;i++)
    {
       buf_pool[i]=(BUF_POOL*)malloc(frame_size);
       buf_pool[i]->_pincount=-1;
       priority[i] = -1;
    }
}
bool database::createDB(char* db_name, long db_size)
{
     database::setBid(open(db_name, O_CREAT, 0777));
     cout << "File creation Status:" << bid << endl;
     close(bid);

     if (bid >= 0)
    {
       database::setBid(open(db_name,O_RDWR));
//        for(int i=0;i<n;i++)
       lseek(bid,num_frames*frame_size,SEEK_SET);
       write(bid,"#",1);
       cout<<"Closing file"<<endl;
        if(!close(bid))
        return true;
    }
    else
        return false;
}

bool database::deleteDB(char* db_name)
{
    long b_id = database::getBid();
    cout<<"Closing File"<<endl;
    if (close(b_id) > 0) {
        cout<<"Deleting database"<<endl;
        remove(db_name);
        return true;
    }
    else
        return false;
}

long database::openDB(char* db_name)
{
    database::setBid(open(db_name, O_RDWR));
    cout<<"Bid"<<bid<<endl;
    if(bid>=0)
    {
        buffer_init();

        for(int i=0;i<num_frames;i++)
         {
            lseek(bid,i*frame_size,SEEK_SET);
            read(bid,buf_pool[i],sizeof(BUF_POOL)-1+p_size*sizeof(char));
         }

    }
    return bid;
}

bool database::closeDB(char* db_name)
{
        int c,i=0,j=0,k;
        k=num_frames-free_frames;
        while(j<free_frames)
        {
         if(buf_pool[i++]->_pincount>=0)
         {
             database::writeIntoDB(bid,buf_pool[i-1],i);
             j++;
         }
        }
    c = close(database::getBid());
    if(c==0)
        return true;
    return false;
}

bool database::readFromDB(long bid, void* buffer, int pageNumber)
{
    int r;
    BUF_POOL* new_page = (BUF_POOL*)malloc(frame_size);
    lseek(bid,frame_size*pageNumber,SEEK_SET);
    r = read(bid,new_page,frame_size);
    cout<<"Num of Bytes Read:"<<r<<endl;
    cout<<"pg_no:"<<pageNumber<<endl;
    cout<<"PageData:"<<new_page->_pagedata<<endl;
    return database::addPage(new_page);
}

bool database::writeIntoDB(long bid, void* buffer, int pageNumber)
{
    BUF_POOL* b1=(BUF_POOL*)malloc(frame_size);
    b1->_pagedata = (char*)buffer;
    b1->_pageno=pageNumber;
    cout<<"WritingPageData:"<<b1->_pagedata<<endl<<"PageNumber:"<<b1->_pageno<<endl;
    lseek(bid,frame_size*pageNumber,SEEK_SET);
    write(bid,b1,frame_size);
}

bool database::addPage(void* buffer)
{
    int i,lru;
        if(free_frames>0)
        {
         for(i=0;i<num_frames;i++)
          {
           if(priority[i]<0)
            {
             buf_pool[i]= (BUF_POOL*)buffer;
             buf_pool[i]->_pincount = 0;
             priority[i]=(int)buf_pool[i]->_pageno;
             cout<<"Adding Page:"<<buf_pool[i]->_pagedata<<endl;
             free_frames--;
             return true;
            }
          }
        }
    lru = priority[0];
    buf_pool[lru]= (BUF_POOL*)buffer;
    buf_pool[lru]->_dirty=0;
    cout<<"Oops!! Why am I here?"<<endl;

    return true;
    return false;
}

void database::getPage(int pageNumber)
{
    int temp,i;
    BUF_POOL* page;
    cout<<"free frames:"<<free_frames<<endl;
    if(free_frames!=num_frames)
    {
    for(i=0;i<(num_frames-free_frames);i++)
    {
        if(buf_pool[i]->_pageno==pageNumber)
        {
        cout<<"Frame found"<<endl;
            if(i<frame_size-1)
            {
                if(priority[i+1]>=0)
            temp = priority[i];
            priority[i]=priority[i+1];
            priority[i+1]=temp;
            }
        cout<<"Page Data:"<<buf_pool[i]->_pagedata<<endl;
            return buf_pool[i];
        }
    }

    }

    cout<<"Loading page from file..."<<endl;
    database::readFromDB(bid,&page,pageNumber);
    cout<<"After Reading Data"<<endl;
    cout<<"Get_Page_Data:"<<page->_pagedata<<endl;
    return page;

}

