/*
 * File:   database.cpp
 * Author: sasi
 *
 * Created on 8 September, 2011, 11:22 PM
 */

#include "BufferManager.h"

#include <stdio.h>
#include "fcntl.h"
#include "unistd.h"
#include <iostream>

using namespace std;

bool BufferManager::createDB(char *db_name, long) {
    BufferManager::setBid(open(db_name, O_CREAT, 0777));
    cout << "File creation Status:" << bid << endl;

    if (bid >= 0)
    {
        if(!close(bid))
        return true;
    }
    else
        return false;

}

bool BufferManager::deleteDB(char *db_name) {

    long b_id = BufferManager::getBid();
    cout<<"Closing File"<<endl;
    if (close(b_id) > 0) {
        cout<<"Deleting database"<<endl;
        remove(db_name);
        return true;
    }
    else
        return false;
}

long BufferManager::openDB(char *db_name) {
    BufferManager::setBid(open(db_name, O_RDWR));
    return bid;
}

bool BufferManager::closeDB(char *db_name) {
    return close(BufferManager::getBid());
}

bool BufferManager::readFromDB(long bid, void* buffer, int pageNum) {
    return read(BufferManager::getBid(), buffer, pageNum);
}

bool BufferManager::writeIntoDB(long bid, void* buffer, int pageNum) {
    return write(BufferManager::getBid(), buffer, pageNum);
}

long BufferManager::getBid() const {
    return bid;
}

char *BufferManager::getDbname() const {
    return dbname;
}

void BufferManager::setBid(long bid) {
    this->bid = bid;
}

void BufferManager::setDbname(char *dbname) {
    this->dbname = dbname;
}

