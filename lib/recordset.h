#define CHAR_EXTRA_BYTES 6
typedef struct t_record {
    char *field_start_offset;                           //Holds information about start of the field (1 or 2 byte depending on record length)
    char *extra_bytes[CHAR_EXTRA_BYTES];                //Holds information about the record itself, like deletion, number of fields etc... (6bytes)
    void *data;                                         //Holds data information
};

//Getters
int get_field_offset_type (t_record *record);            //1 byte or 2 byte
int get_offset_value (t_record *record,int f_no);        //Offset of the field within a record
int get_null_bit (t_record *record);                     //Is a field null or not
int get_deleted_flag (t_record *record);                 //Is this record deleted or not
int get_number_of_fields (t_record *record);             //Returns the number of fields in this record
t_record* get_next_record (t_record *record);            //Get next record in the hierarchy and return it

//Setters
int set_field_offset_type (t_record *record);            
int set_offset_value (t_record *record,int f_no);
int set_null_bit (t_record *record);
int set_deleted_flag (t_record *record);
int set_number_of_fields (t_record *record);
int set_next_record (t_record *record);