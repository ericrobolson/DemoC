#include <stdio.h>
#include "core_mem.h"

/*
CFLAGS
- MEM_CHECK = Print out all allocations and frees.
*/

#ifdef MEM_CHECK
#define malloc(s) ({                                                             \
    void *ptr = mymalloc(s);                                                     \
    printf("mem_test pointer '%p': %s:%i - .malloc\n", ptr, __FILE__, __LINE__); \
    ptr;                                                                         \
})

#define free(ptr) ({                                                          \
    printf("mem_test pointer '%p': %s:%i - free\n", ptr, __FILE__, __LINE__); \
    ptr;                                                                      \
})
#else
#define malloc(s) ({         \
    void *ptr = mymalloc(s); \
    ptr;                     \
})

#define free(ptr) ({ \
    ptr;             \
})
#endif