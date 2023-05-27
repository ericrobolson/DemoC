#include <stdio.h>
#include "vec2.h"

/// @brief Prints out a Vec2
/// @param v
void Vec2_print(Vec2 v)
{
    printf("Vec2{x: %i, y: %i}", v.x, v.y);
}

Vec2 Vec2_add(Vec2 a, Vec2 b)
{
    Vec2 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

Vec2 Vec2_sub(Vec2 a, Vec2 b)
{
    Vec2 c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}
