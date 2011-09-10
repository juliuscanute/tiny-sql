//
//  page.cpp
//  tiny-sql-test
//
//  Created by Julius Canute on 9/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "page.h"
int Page_Info::get_table_type() {
    return table_type;
}
int Page_Info::set_table_type(int t_type) {
    table_type = t_type;
    return 0;
}
int Page_Info::get_page_no() {
    return page_no;
}
int Page_Info::set_page_no(int p_no) {
    page_no = p_no;
    return 0;
}
int Page_Info::get_page_previous() {
    return p_prev;
}
int Page_Info::set_page_previous(int p_previous) {
    p_prev = p_previous;
    return 0;
}
int Page_Info::get_page_next() {
    return p_next;
}
int Page_Info::set_page_next(int p_nex) {
    p_next = p_nex;
    return 0;
}
int Page_Info::get_free_bytes() {
    int f_bytes;
    f_bytes = (((int)free_bytes[0])<<8) | (int)free_bytes[1] ;
    return f_bytes;
}
int Page_Info::set_free_bytes(int f_bytes) {
    free_bytes[0] = (char)((f_bytes & 0xFF00) >> 8);
    free_bytes[1] = (char)(f_bytes & 0x00FF);
    return 0;
}
int Page_Info::get_free_record() {
    int f_record;
    f_record = (((int)free_record[0])<<8) | (int)free_record[1] ;
    return f_record;
}
int Page_Info::set_free_record(int f_rec) {
    free_record[0] = (char)((f_rec & 0xFF00) >> 8);
    free_record[1] = (char)(f_rec & 0x00FF);
    return 0;
}
int Page_Info::get_first_record() {
    int f_record;
    f_record = (((int)first_record[0])<<8) | (int)first_record[1] ;
    return f_record;
}
int Page_Info::set_first_record(int f_rec) {
    first_record[0] = (char)((f_rec & 0xFF00) >> 8);
    first_record[1] = (char)(f_rec & 0x00FF);
    return 0;
}
int Page_Info::get_num_records() {
    int n_records;
    n_records = (((int)num_records[0])<<8) | (int)num_records[1] ;
    return n_records;
}
int Page_Info::set_num_records(int n_rec) {
    num_records[0] = (char)((n_rec & 0xFF00) >> 8);
    num_records[1] = (char)(n_rec & 0x00FF);
    return 0;
}
int Page_Info::get_check_sum() {
    return check_sum;
}
int Page_Info::set_check_sum(long c_sum) {
    check_sum =  c_sum;
    return 0;
}

