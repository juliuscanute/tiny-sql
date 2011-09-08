#ifndef PAGE_H
#define PAGE_H
#include "page.h"
#endif
#define MAX_DB_FILE 40
typedef struct tsql_ptr {
    int db_id;
    char *db_name;
    int file_id; 
};

int create_db(tsql_ptr *db_ptr);
int open_db(tsql_ptr *db_ptr);
int read_page(tsql_ptr *db_ptr,int page_no);
int write_page(tsql_ptr *db_ptr,page_header *page);
int delete_db(tsql_ptr *db_ptr);