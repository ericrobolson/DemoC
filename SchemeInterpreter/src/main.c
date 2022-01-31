#include <stdio.h>
#include "utest.h"
#include "app.h"

#ifdef UNIT_TEST
UTEST_MAIN();
#else
UTEST_STATE();

int main()
{
	return app();
}

#endif
