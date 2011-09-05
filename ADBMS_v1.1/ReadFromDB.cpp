#include "ReadFromDB.h"
#include "fcntl.h"
#include "unistd.h"
#include <iostream>

using namespace std;

bool ReadFromDB(long bid,void *buffer,int pageNumber)
{
  int i,fid;
  char data[20];
   for(i=0;i<db_ptr;i++)
    {
     if(dptr[i].bid==bid)
      {
       fid=open(dptr[i].dbname,O_APPEND);
       if(fid<0)
        return false;
       else
        {
           if(read(f_id,data,10)>0)
            {
             cout <<"Data:" << data <<endl;
             close(fid);
             return true;
            }
           else
            return false;
        }
      }
    }

}
