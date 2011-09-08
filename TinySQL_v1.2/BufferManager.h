/* 
 * File:   BufferManager.h
 * Author: sasi
 *
 * Created on 9 September, 2011, 12:41 AM
 */

#ifndef BUFFERMANAGER_H
#define	BUFFERMANAGER_H

class BufferManager
{
private:
	long bid;
	char* dbname;
public:
	bool createDB(char *db_name, long db_size);
	long openDB(char *db_name);
	bool closeDB(char *db_name);
	bool deleteDB(char *db_name);
	bool readFromDB(long bid,void *buffer,int pageNumber);
	bool writeIntoDB(long bid,void *buffer,int pageNumber);
	long getBid() const;
    char *getDbname() const;
    void setBid(long  bid);
    void setDbname(char *dbname);


};

#endif	/* BUFFERMANAGER_H */

