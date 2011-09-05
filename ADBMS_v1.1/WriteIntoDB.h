#include "ADBMS.h"
#include "fcntl.h"
#include "unistd.h"

bool WriteIntoDB(long bid,void *buffer,int pageNumber);
