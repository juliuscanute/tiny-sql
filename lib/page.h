//
//  page.h
//  tiny-sql-test
//
//  Created by Julius Canute on 9/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef tiny_sql_test_page_h
#define tiny_sql_test_page_h
#include "recordset.h"
#define FREE_BYTES 4 + 4 + 4 + 2 + 2 + 2 + 2 + 8               //(tabel type) + (previous field) + (next field)+ (first record field) + (free bytes field) + (number of records field)+ (sizeof recordset) + (checksum)
#define PAGE_SIZE 8192
#define FIELD_SIZE 2
#define PAGE_ADD_SIZE 4
class Page_Info {

private:
    int table_type;                             //Table to which the page belongs
    int page_no;                                //Page number
    int p_prev;                                 //Points to the previous page
    int p_next;                                 //Points to the   page
    char first_record[FIELD_SIZE];                  //Points to the first record
    char free_record[FIELD_SIZE];               //Points to the first record that is free
    char free_bytes[FIELD_SIZE];                //Information about number of free bytes
    char num_records[FIELD_SIZE];               //Points to the number of records(default 2 bytes)
    char record_set[PAGE_SIZE - FREE_BYTES];    //Points to the linked list of recordset    
    long check_sum;                        //Page checksum Information(8 bytes)

public:
    //Getters
    int get_table_type();
    int get_page_no();
    int get_page_previous();
    int get_page_next();
    int get_free_bytes();
    int get_free_record();
    int get_first_record();
    int get_num_records();
    int get_check_sum();
    
    //Setters
    int set_table_type(int t_type);
    int set_page_no(int p_no);
    int set_page_previous(int p_previous);
    int set_page_next(int p_nex);
    int set_free_bytes(int f_bytes);
    int set_free_record(int f_rec);
    int set_first_record(int f_rec);
    int set_num_records(int n_rec);
    int set_check_sum(long c_sum);
};
#endif
