// Do not build if using unit tests.
#ifndef UNIT_TEST

#include "circle_buffer.h"
#include <stdio.h>

int main()
{

#ifdef _WIN64
    printf("Is windows OS");
#endif

    return 0;
}

#endif
