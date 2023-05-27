#pragma once
#include "types.h"

typedef struct Vec2
{
    i32 x;
    i32 y;
} Vec2;

/// @brief Prints out a Vec2
/// @param v
void Vec2_print(Vec2 v);

/// @brief Adds two vectors together
/// @param a
/// @param b
/// @return
Vec2 Vec2_add(Vec2 a, Vec2 b);

/// @brief Subtracts a vector from another.
/// @param a
/// @param b
/// @return
Vec2 Vec2_sub(Vec2 a, Vec2 b);
