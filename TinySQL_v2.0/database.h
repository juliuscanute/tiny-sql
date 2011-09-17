/* 
 * File:   database.h
 * Author: sasi
 *
 * Created on 16 September, 2011, 10:27 PM
 */

#ifndef DATABASE_H
#define	DATABASE_H

#include "bufferManager.h"

class database
{
    private:
        long bid;

    public:
	bool createDB(char *db_name, long db_size);
	long openDB(char *db_name);
	bool closeDB(char *db_name);
	bool deleteDB(char *db_name);
	bool readFromDB(long bid,void *buffer,int pageNumber);
	bool writeIntoDB(long bid,void *buffer,int pageNumber);
        bool addPage(BUF_POOL* buffer);

    long getBid() const {
        return bid;
    }

    void setBid(long bid) {
        this->bid = bid;
    }


};

#endif	/* DATABASE_H */

