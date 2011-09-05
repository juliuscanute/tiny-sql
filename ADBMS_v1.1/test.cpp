#include "CreateDB.cpp"
#include <stdio.h>
#include "OpenDB.cpp"
#include "WriteIntoDB.cpp"
#include "ReadFromDB.cpp"
#include "stdlib.h"

int main()
 {

   char dbname[10]="sample.db";
   int  input, i,dbs_open = 0;
   long b_id;
   db_ptr = 0;
     system("clear");
   cout << "1. Create_DB, 2. Open_DB, 3. WriteInto_DB, 4. ReadFrom_DB, 5. Exit"<<endl;
   while(1)
    {
     cout << "tsql >" ;

     cin >> input;

     switch (input)
      {
       case 1:
               {
                 if(createDB(dbname, 100)==true)
                  printf("CREATED\n");
  
                 else
                  printf("FAILED to \n");
                 break;
               }
       case 2:
               {
                 b_id = openDB(dbname);

                 if(b_id == DB_ALREADY_OPEN)
                   cout << "Database is already open" <<endl; 

                 else if(b_id == 0)
                  cout << "Error in opening file " << dbname << endl;

                 else
                   cout<<"Opened DB" << endl;
                
                 break;
               }
        case 3:
               {
                 if(WriteIntoDB(b_id,dbname,1)==true)
                  cout<< "Data written" << endl;
                 else 
                  cout<< "Failed to Write" << endl;
                 break;
               }
        case 4:
               {
                 if(ReadFromDB(b_id,dbname,1)==true)
                  cout<< "Data written" << endl;
                 else 
                  cout<< "Error in writing data" << endl;
                 break;
               }
        case 5:
                 exit(0);
      }
    
    }
   
   return 0;
 }

