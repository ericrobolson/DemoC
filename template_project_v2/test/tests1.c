#include "utest.h"

UTEST(foo, bar)
{
    ASSERT_TRUE(1);
}

UTEST(Testy, T_1_Plus_1_Eq_2)
{
    ASSERT_EQ(1 + 1, 2);
}
