#include "g_malloc.h"
#include <stdlib.h>

void *g_malloc(size_t size)
{
	return malloc(size);
}
