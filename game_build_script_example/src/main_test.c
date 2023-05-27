#include <assert.h>
#include "vec2.h"

void Vec2_tests()
{
    Vec2 a;
    Vec2 b;

    a.x = 1;
    a.y = 2;

    b.x = 3;
    b.y = 4;

    Vec2 v = Vec2_add(a, b);

    assert(v.x == 4);
    assert(v.y == 6);
}

#ifdef TEST
int main()
{
    Vec2_tests();
}
#endif
