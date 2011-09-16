#include "database.h"
#include "page_info.h"


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
       database::setBid(open(db_name,O_WRONLY));
        for(int i=0;i<db_size;i++)
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

    for(int i=0;i<num_frames;i++)
    {
        buffer_init();
        lseek(bid,sizeof(frame)*i,SEEK_SET);
        read(bid,sizeof(frame));
    }
    return bid;

}

bool database::closeDB(char* db_name)
{
    int c = close(database::getBid());
    if(c==0)
        return true;
    return false;
}

bool database::readFromDB(long bid, void* buffer, int pageNumber)
{
    lseek(bid,p_size*pageNumber,SEEK_SET);
    read(bid,buffer,sizeof(frame));
    addPage(buffer);
}

bool database::writeIntoDB(long bid, void* buffer, int pageNumber)
{
    lseek(bid,p_size*pageNumber,SEEK_SET);
    write(bid,buffer,sizeof(frame));
}

bool database::addPage(void* buffer)
{
    if()
}