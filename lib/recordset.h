//
//  recordset.h
//  tiny-sql-test
//
//  Created by Julius Canute on 9/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef tiny_sql_test_recordset_h
#define tiny_sql_test_recordset_h
#define CHAR_EXTRA_BYTES 6
#define FIELD_SIZE 2
#define NULL 0
class Record_Set{
    
private:
    char *field_start_offset;                           //Holds information about start of the field (2 byte depending on record length
    char extra_bytes[CHAR_EXTRA_BYTES];                //Holds information about the record itself, like deletion, number of fields etc... 
    void *data;                                         //Holds data information
    
public:
    //Constructor
    Record_Set(int n_fields,void *t_data);
    //Getters
    
    int get_offset_value (int f_no);         //Offset of the field within a record
    int get_null_bit (int f_no);                     //Is a field null or not
    int get_deleted_flag ();                 //Is this record deleted or not
    int get_number_of_fields ();             //Returns the number of fields in this record
    int get_next_record_offset();
    //Record_Set get_next_record ();           //Get next record in the hierarchy and return it
    
    //Setters
    
    int set_offset_value (int f_no,int f_offset);
    int set_null_bit (int f_no,int b_null);
    int set_deleted_flag (int d_flag);
    int set_number_of_fields (int n_fields);
    int set_next_record_offset (int a_offset);
    //Destructor
    ~Record_Set();
};
#endif
