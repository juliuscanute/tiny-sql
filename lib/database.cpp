//
//  database.cpp
//  tiny-sql-test
//
//  Created by Sasi on 9/10/11.
//  Modified by Julius on 9/10/11
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "database.h"
int Database_Info::create_db(char *db_name) {
    db_id = open(db_name, O_CREAT, 0777);
    this->db_name = db_name;
    
    if (db_id >= 0)
    {
        if(!close(db_id))
            return 0;
    }
    
    return 1;
    
}

int Database_Info::delete_db() {
    
    
    
    if (close(db_id) > 0) {
    
        remove(db_name);
        return 0;
    }
    else
        return 1;
}

int Database_Info::open_db() {
    db_id = open(db_name, O_RDWR);
    return db_id;
}

int Database_Info::close_db() {
    long c = close(Database_Info::get_bid());
    if(c==0)
        return 0;
    return 1;
}

int Database_Info::read_page_db(Page_Info* buffer, int page_num) {
    if(lseek(Database_Info::get_bid(),(page_num*PAGE_SIZE),SEEK_SET)<0)
        return 1;
    long r =  read(Database_Info::get_bid(), buffer, PAGE_SIZE);
    if(r>0)
        return 0;
    
    return 1;
}

int Database_Info::write_page_db(Page_Info* buffer, int page_num) {
    if(lseek(Database_Info::get_bid(),(page_num*PAGE_SIZE),SEEK_SET)<0)
        return 1;
    long w = write(Database_Info::get_bid(), buffer,PAGE_SIZE);
    if(w>0)
        return 0;
    
    return 1;
}

long Database_Info::get_bid() const {
    return db_id;
}

char* Database_Info::get_db_name() const {
    return db_name;
}





