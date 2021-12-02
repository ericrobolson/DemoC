#include <stdint.h>
#include <stdbool.h>

struct Vec2
{
    int32_t x;
    int32_t y;
};

struct Aabb
{
    struct Vec2 min;
    struct Vec2 max;
};

struct GCollideable
{
    struct Vec2 position;
    struct Vec2 previous_position;

    struct Aabb bounding_box;
    int64_t idx;       // index of the collideable
    int64_t entity_id; // Entities shouldn't collide with each other

    int16_t collision_count;
    int16_t max_collisioins;
    struct GCollision *collisions;
};

struct GCollision
{
    int64_t other_idx;
    struct Vec2 vector;
};

struct GPhysics
{
    int64_t capacity;
    int64_t count;
    struct GCollideable *collideables;
};

/// Creates a new physics instance
struct GPhysics *g_physics_new();

/// Resets the physics
void g_physics_reset(struct GPhysics *physics);

/// Adds a new collideable
struct GCollideable *g_physics_add_collideable(struct GPhysics *physics);

// Goes through and calculates all physics
void g_physics_tick(struct GPhysics *physics);
