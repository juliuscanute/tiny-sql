#include "CreateDB.cpp"
#include <stdio.h>

int main()
 {
	char dbname[10] = "db1.tdb";
  if(createDB(dbname, 100)==true)
   printf("SUCCESS\n");
  else
   printf("FAILURE\n");

  return 0;
 }

