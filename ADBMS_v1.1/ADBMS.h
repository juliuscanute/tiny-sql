#define MAX_DB_FILE 10

#ifndef _dptr
struct TSqlDptr
{
	long bid;
	char *dbname;
	long fid;
}dptr[MAX_DB_FILE];
#define _dptr 10
#endif

typedef struct
{
	bool _dirty;
	long _pincount;
	unsigned long _priority;
	long _pageno;
	char _pagedata[1];
} frame_str,*lp_frame_str;
