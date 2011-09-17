/* 
 * File:   bufferManager.h
 * Author: sasi
 *
 * Created on 17 September, 2011, 1:43 AM
 */

#ifndef BUFFERMANAGER_H
#define	BUFFERMANAGER_H

#define p_size 1024
#define num_frames 8

typedef struct
{
bool _dirty;
long _pincount;
unsigned long _priority;
long _pageno;
char _pagedata[1];
}BUF_POOL;

BUF_POOL* buf_pool[num_frames];
int free_frames = num_frames;
int priority[num_frames];

bool buffer_init();

#endif	/* BUFFERMANAGER_H */

