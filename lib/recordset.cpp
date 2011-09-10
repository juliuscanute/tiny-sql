//
//  recordset.cpp
//  tiny-sql-test
//
//  Created by Julius Canute on 9/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "recordset.h"


Record_Set::Record_Set(int n_fields,void *t_data) {
    field_start_offset=new char[n_fields*FIELD_SIZE];
    Record_Set::set_number_of_fields(n_fields);
    data=t_data;
}
int Record_Set::set_offset_value(int f_no,int f_offset) {
    int n_field = Record_Set::get_number_of_fields();
    if (f_no < n_field) {
        field_start_offset[f_no * 2] = (char)((f_offset & 0xFF00)>>8) ;                          //First push the first higher order byte
        field_start_offset[(f_no * 2) + 1] = (char)(f_offset & 0x00FF) ;                         //Then push the second lower order byte
        return 0;
    }
    return 1;
}

int Record_Set::get_offset_value(int f_no) {
    int n_field = Record_Set::get_number_of_fields();
    int offset_value = 0;
    if (f_no < n_field) {
        offset_value = ((((int)field_start_offset[f_no * 2])&0x7F)<<8) | ((int)field_start_offset[(f_no * 2)+1]);
        return offset_value;
    }
    return 1;
}
int Record_Set::get_number_of_fields() {
    int i_num_fields=0;
    i_num_fields = (((int)extra_bytes[0])<<2) | (((int)extra_bytes[1] & 0xC0)>>6) ;
    return i_num_fields;
}

int Record_Set::set_number_of_fields(int n_fields) {
    extra_bytes[0] = (char)((n_fields & 0x3FC) >> 2);                                   //Get the starting 8 bits of the 10 bits
    extra_bytes[1] = (char)((n_fields & 0x3) << 6);                                     //Get the last 2 bits of the remaining string
    return 0;
}

int Record_Set::set_null_bit(int f_no,int b_null) {
    int n_field = Record_Set::get_number_of_fields();
    if (f_no < n_field) {
        field_start_offset[f_no*2] = field_start_offset[f_no*2] | ((b_null & 0x01)<<7) ;
        return 0;
    }
    return 1;
}

int Record_Set::get_null_bit(int f_no) {
    int n_field = Record_Set::get_number_of_fields();
    int b_null = 0;
    if (f_no < n_field) {
        b_null = (field_start_offset[f_no*2] & 0x80) >> 7;
        return b_null;
    }
    return -1;
}

int Record_Set::set_deleted_flag(int d_flag) {
    extra_bytes[1] = (char)(((int)extra_bytes[1] & 0xC0) | ((d_flag & 0x01) << 5));
    return 0;
}

int Record_Set::get_deleted_flag() {
    int d_flag = 0;
    d_flag = ((int)extra_bytes[1] & 0x20) >> 5;
    return d_flag;
}

int Record_Set::get_next_record_offset() {
    int a_offset = 0;
    a_offset = (((int)extra_bytes[4]) << 8) | ((int)extra_bytes[5]);
    return a_offset;
}

int Record_Set::set_next_record_offset(int a_offset) {
    extra_bytes[4] = (char)((a_offset & 0xFF00) >> 8);
    extra_bytes[5] = (char)(a_offset & 0x00FF);
    return 0;
}
Record_Set::~Record_Set() {
    delete field_start_offset;
    data = NULL;
}