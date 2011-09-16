/* 
 * File:   database.h
 * Author: sasi
 *
 * Created on 16 September, 2011, 10:27 PM
 */

#ifndef DATABASE_H
#define	DATABASE_H



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
        bool addPage(void* buffer);

    long getBid() const {
        return bid;
    }

    void setBid(long bid) {
        this->bid = bid;
    }

    long getP_size() const {
        return p_size;
    }

    void setP_size(long p_size) {
        this->p_size = p_size;
    }

};

#endif	/* DATABASE_H */

