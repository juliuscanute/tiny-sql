#include "CreateDB.h"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace std;

bool createDB(char *db_name, long sizeOfDB)
{
	int f_id = open(db_name,O_CREAT,0777);
	cout << "File creation Status" << f_id;

	if(!close(f_id))
		return true;
	else
		return false;
}
