
#include "bufferManager.h"
#include "page_info.h"
#include <alloca.h>

bool buffer_init()
{
    frame_ptr = alloca(p_size);
}