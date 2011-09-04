#ifndef RECORDSET_H
#define RECORDSET_H
#include "recordset.h"
#endif

#define FIELD_SIZE 2
typedef struct page_header {
    int table_type;                     //Table to which the page belongs
    page_header *p_prev;                //Points to the previous page
    page_header *p_next;                //Points to the next page
    t_record *t_free;                   //Points to the first record that is free
    char *free_bytes[FIELD_SIZE];       //Information about number of free bytes
    char *num_records[FIELD_SIZE];      //Points to the number of records(default 2 bytes)
    long long check_sum;                //Page checksum Information(8 bytes)
}

//Getters
int get_table_type(page_header *page);
page_header *get_prev_page(page_header *page);
page_header *get_next_page(page_header *page);
t_record *get_free_record(page_header *page);
int get_free_bytes(page_header *page);
int get_num_records(page_header *page);
t_record *get_record(page_header *page);
int get_check_sum(page_header *page);

//Setters
int set_table_type(page_header *page);
int *set_prev_page(page_header *page);
int *set_next_page(page_header *page);
t_record *set_free_record(page_header *page,t_record *record);
int set_free_bytes(page_header *page);
int set_num_records(page_header *page);
int set_check_sum(page_header *page);