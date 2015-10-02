#ifndef __dbg_h__
#define __dbg_h__


#include <stdio.h>
#include <string.h>
#define DS_DEBUG DS_DEBUG
#define MAX_LEVEL 5
#define CURRENT_LEVEL 3


#ifdef NDEBUG
#define Debug(level,Message,...)
#else

#define Debug(level,Message,...) do{\
        if( level < CURRENT_LEVEL && level < MAX_LEVEL && level > 0)\
        {\
                    printf("[DS_DEBUG(%d)] ",level);\
                    printf("[%s] @%s---%d:  \n", __func__,__FILE__, __LINE__);\
                    printf(Message,##__VA_ARGS__);\
        }\
}while(0)
#endif
#endif

