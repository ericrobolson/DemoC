#include <stdlib.h>

/// @brief Wrapper for malloc.
/// @param s the size of it.
/// @return a pointer to the memory.
void *mymalloc(size_t s)
{
    return malloc(s);
}

/// @brief Frees the given pointer
/// @param p
void myfree(void *p)
{
    free(p);
}
