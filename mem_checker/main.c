#include <stdio.h>
#include "core.h"

int main()
{
    int *ptr = (int *)malloc(100 * sizeof(int));
    void *ptr2 = malloc(32);
    free(ptr2);
    free(ptr);
    return 0;
}