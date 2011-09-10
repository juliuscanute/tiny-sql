//
//  database.h
//  tiny-sql-test
//
//  Created by Julius Canute on 9/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef tiny_sql_test_database_h
#define tiny_sql_test_database_h

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "page.h"
class Database_Info
{
private:
	long db_id;
	char *db_name;
public:
	int create_db(char *db_name);
	int open_db();
	int close_db();
	int delete_db();
	int read_page_db(Page_Info *buffer,int page_number);
	int write_page_db(Page_Info *buffer,int page_number);
	long get_bid() const;
    char* get_db_name() const;

};
#endif
