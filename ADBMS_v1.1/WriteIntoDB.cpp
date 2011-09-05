#include "WriteIntoDB.h"
#include <iostream>

using namespace std;
bool WriteIntoDB(long bid,void *buffer,int pageNumber)
{
  int i,fid;
   cout<<"db pointer:"<<db_ptr<<endl;
   for(i=0;i<db_ptr;i++)
    {
     cout<<"Checking index:"<<i<<endl<<"db name:"<<dptr[i].dbname<<endl;
     if(dptr[i].bid==bid)
      {
       fid=open(dptr[i].dbname,O_APPEND);
       if(fid<0)
        return false;
       else
        {
           cout<<"Writing data into file..."<<endl;
           if(write(fid,buffer,10)>0)
            {
             close(fid);
           cout<<"write success..."<<endl;

             return true;
            }
           else
            return false;
        }
      }
    }
           cout<<"Oops!!..."<<endl;
   return false;
}
