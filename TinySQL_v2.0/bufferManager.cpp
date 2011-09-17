
#include "bufferManager.h"
#include <malloc.h>

bool buffer_init()
{

    for(int i=0;i<num_frames;i++)
    {
       buf_pool[i]=(BUF_POOL*)malloc((sizeof(BUF_POOL)-1)+p_size*sizeof(char));
       buf_pool[i]->_pincount=-1;
    }

}