/* 
 * File:   main.cpp
 * Author: sasi
 *
 * Created on 16 September, 2011, 10:26 PM
 */
#include <stdio.h>
#include <malloc.h>
#include <cstdlib>
#include "database.h"
#include <iostream>
#include <vector>
#include<string>

using namespace std;

/*
 * 
 */
int main() {
    database dba;
    char data[25];
    int op;
    long b_id;
    string db;
    string query;

        system("clear");
        cout<<"1. CreateDB 2. OpenDB, 3. WriteIntoDB, 4. ReadFromDB, 5. DeleteDB, 6. CloseDB, 7. Quit"<<endl;
    while(1)
    {
//        getline(std::cin, query);
        cout<<"Query>";
        cin>>op;
        switch(op)
        {
            case 1:
            {
              //Create Database
                cout<<"DB Name:";
                cin>>db;
              if(!dba.createDB("sample.db",1000))
              cout<<"Created Database"<<endl;
              break;
            }

            case 2:
            {
              //Open Database
              b_id = dba.openDB("sample.db");
              if(b_id>=0)
              cout<<"File Opened"<<endl;
              break;
            }

            case 4:
            {
               //Write into Database
               char* file = "SampleData";
               if(dba.writeIntoDB(b_id,file,1)>0)
               cout<<"Data is written into file"<<endl;
               break;
            }

            case 3:
            {
               //Read from Database
               cout<<"Reading data from file"<<endl;
               if(dba.readFromDB(b_id,data,1)>0)
               cout<<data<<endl;
               break;
            }

            case 5:
            {
              //Delete Database
             if(dba.deleteDB("sample.db"))
             cout<<"Success"<<endl;
             break;
            }

            case 6:
            {

            }

            case 7:
                exit(0);

        }

    }

  
    return 0;
}

