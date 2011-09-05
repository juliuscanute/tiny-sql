#define MAX_DB_FILE 10
#define DB_CREATED 1
#define DB_EXISTS 2
#define DB_OPENED 3
#define DB_ALREADY_OPEN 4
#define DB_NOT_FOUND 5
#define DB_CLOSE 6
#define SUCCESS 7
#define FAILURE 8

#ifndef _dptr

int f_id;
int db_ptr;

struct TSqlDptr
{
	long bid;
	char *dbname;
	long fid;
}dptr[MAX_DB_FILE];
#define _dptr 10
#endif

#ifndef _frame_str
typedef struct
{
	bool _dirty;
	long _pincount;
	unsigned long _priority;
	long _pageno;
	char _pagedata[1];
} frame_str,*lp_frame_str;
#define _frame_str
#endif
