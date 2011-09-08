/*
 * File:   ui.cpp
 * Author: sasi
 *
 * Created on 8 September, 2011, 11:26 PM
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "BufferManager.h"
/*
 *
 */

using namespace std;

int main()
{
    BufferManager dba;
    char data[25];

    //Create Database
    if(!dba.createDB("sample.db",1000))
     cout<<"Created Database"<<endl;

    //Open Database
    long b_id = dba.openDB("sample.db");
    if(b_id>=0)
        cout<<"File Opened"<<endl;

    //Write into Database
    char* file = "SampleData";
    if(dba.writeIntoDB(b_id,file,1)>0)
        cout<<"Data is written into file"<<endl;

    //Read from Database
    cout<<"Reading data from file"<<endl;
    if(dba.readFromDB(b_id,data,1)>0)
        cout<<data<<endl;


    //Delete Database
    if(dba.deleteDB("sample.db"))
        cout<<"Success"<<endl;

    return 0;
}
