#include "database.h"
#include "bufferManager.h"

#include <malloc.h>
#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;


bool database::createDB(char* db_name, long db_size)
{
     database::setBid(open(db_name, O_CREAT, 0777));
     cout << "File creation Status:" << bid << endl;
     close(bid);

     if (bid >= 0)
    {
       database::setBid(open(db_name,O_RDWR));
//        for(int i=0;i<n;i++)
       lseek(bid,num_frames*(sizeof(BUF_POOL)-1+sizeof(char)*p_size),SEEK_SET);
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
    if(bid>=0)
    {
        buffer_init();

        for(int i=0;i<num_frames;i++)
         {
            lseek(bid,i*(sizeof(BUF_POOL)-1+p_size*sizeof(char)),SEEK_SET);
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
    BUF_POOL* new_page = (BUF_POOL*)malloc(sizeof(BUF_POOL));
    lseek(bid,p_size*pageNumber,SEEK_SET);
    read(bid,new_page,(sizeof(BUF_POOL)-1+p_size*sizeof(char)));
    return database::addPage(new_page);
}

bool database::writeIntoDB(long bid, void* buffer, int pageNumber)
{
    lseek(bid,(sizeof(BUF_POOL)-1+p_size*sizeof(char))*pageNumber,SEEK_SET);
    write(bid,buffer,(sizeof(BUF_POOL)-1+p_size*sizeof(char)));
}

bool database::addPage(BUF_POOL* buffer)
{
    int i,lru;
        if(free_frames>0)
        {
         for(i=0;i<num_frames;i++)
          {
           if(buf_pool[i]->_pincount<0)
            {
             buf_pool[i]= buffer;
             buf_pool[i]->_pincount = 0;
             free_frames--;
             return true;
            }
          }
        }

    for(i=0;i<num_frames;i++)
    {
        lru = priority[i];
        if(buf_pool[lru]->_pincount==0)
        {
            buf_pool[i]= buffer;
            buf_pool[i]->_pincount = 0;
            return true;
        }
    }
    return false;
}

