/* 
 * File:   page_info.h
 * Author: sasi
 *
 * Created on 17 September, 2011, 1:09 AM
 */

#ifndef PAGE_INFO_H
#define	PAGE_INFO_H
#define p_size 1024
#define num_frames 8

typedef struct
{
bool _dirty;
long _pincount;
unsigned long _priority;
long _pageno;
char _pagedata[1];
}frame;


typedef struct
{
//    char* t_name;
    frame* free_frame;
    frame* first;
    frame* last;
}pg_header;


#endif	/* PAGE_INFO_H */

