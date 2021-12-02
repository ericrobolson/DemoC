
#include "g_free.h"
#include <stdlib.h>

void g_free(void *block)
{
	free(block);
}
