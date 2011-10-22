#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H
#define p_size 1024
#define num_frames 8

#define MAX_FILE_NAME 25
#define MAX_DB 5
#define NUM_FRAMES 8
#define PAGE_SIZE 1024

typedef struct
{
bool _dirty;
long _pincount;
unsigned long _priority;
long _pageno;
char* _pagedata;

}BUF_POOL;

typedef struct
 {
   int bid;
   char db[MAX_FILE_NAME];
 }db_index;

struct p_que
{
 BUF_POOL* page;
 int bid;
 bool lru;
 struct p_que *next;
 struct p_que *prev;
};

struct free_frames
{
    BUF_POOL* frame;
    struct free_frames* next;
    struct p_que* p;
};

typedef struct
 {
  int free_frames,dbs_open,priority[NUM_FRAMES];
  long frame_size; // = sizeof(BUF_POOL)-1+sizeof(char)*PAGE_SIZE;
  struct p_que *lru, *mru;
  struct free_frames* first_free_frame;
  struct free_frames* last_free_frame;
 }frame_header;



class buffer
 {
public:
    BUF_POOL* buf_pool;
//    frame_header* h;
//    db_index* dbi;
    bool buf_init();
    bool createDB(char* dbname,int numPages);
    long openDB(char* dbname);
    bool closeDB(char* dbname);
    bool deleteDB(char* dbname);
    bool readFromDB(int bid,BUF_POOL *buffer,int pageNumber);
    bool writeIntoDB(int bid,BUF_POOL *buffer,int pageNumber);
    BUF_POOL* ReadPage(int bid,int PageNumber);
    bool WritePage(int bid,BUF_POOL* buffer);
    char* addExt(char* dbname);
    void test_buffer();
    void sort(int i);

 };

#endif // BUFFERMANAGER_H
