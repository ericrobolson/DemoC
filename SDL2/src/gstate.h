#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_ENTITIES 1000

typedef int32_t i32;
typedef uint8_t u8;

typedef struct GAabb
{
    i32 width;
    i32 height;
} GAabb;

typedef struct GColor
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} GColor;

typedef struct GPosition
{
    i32 x;
    i32 y;
} GPosition;

typedef struct GState
{
    bool entities[MAX_ENTITIES];
    GAabb aabbs[MAX_ENTITIES];
    GColor colors[MAX_ENTITIES];
    GPosition positions[MAX_ENTITIES];
    GPosition positions_previous[MAX_ENTITIES];
    uint64_t max_entities;
} GState;

typedef struct StaticData
{
} StaticData;

typedef struct GManifold
{
    i32 normal_x;
    i32 normal_y;
} GManifold;

// Returns a new instance of the state.
GState
gstate_new()
{
    GState state;
    state.max_entities = MAX_ENTITIES;

    // Init each entity
    GColor color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;

    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        state.entities[i] = false;
        state.aabbs[i].width = 0;
        state.aabbs[i].height = 0;
        state.colors[i] = color;
        state.positions[i].x = 0;
        state.positions[i].y = 0;
        state.positions[i].x = 0;
        state.positions_previous[i].x = 0;
        state.positions_previous[i].y = 0;
    }

    // begin debug
    int e = 0;
    state.entities[e] = true;
    state.aabbs[e].width = 10;
    state.aabbs[e].height = 10;
    state.positions[e].x = 0;
    state.positions[e].y = 20;

    e = 2;
    state.entities[e] = true;
    state.aabbs[e].width = 30;
    state.aabbs[e].height = 30;
    state.positions[e].x = 0;
    state.positions[e].y = 200;

    // end debug

    return state;
}

/*
 * Physics
 */

/// Returns whether there was a collision or not.
bool gcollision_aabb(GAabb a, GPosition a_pos, GAabb b, GPosition b_pos, GManifold *manifold)
{
    i32 a_x1, a_x2, a_y1, a_y2;
    i32 b_x1, b_x2, b_y1, b_y2;

    a_x1 = a_pos.x;
    a_y1 = a_pos.y;
    a_x2 = a_pos.x + a.width;
    a_y2 = a_pos.y + a.height;

    b_x1 = b_pos.x;
    b_y1 = b_pos.y;
    b_x2 = b_pos.x + b.width;
    b_y2 = b_pos.y + b.height;

    bool x_overlaps = a_x1 <= b_x1 && b_x1 <= a_x2 || b_x1 <= a_x1 && a_x1 <= b_x2;
    ;

    if (!x_overlaps)
    {
        return false;
    }

    bool y_overlaps = a_y1 <= b_y1 && b_y1 <= a_y2 || b_y1 <= a_y1 && a_y1 <= b_y2;

    return x_overlaps && y_overlaps;
}

// Executes a tick of the simulation.
void gtick_sim(GState *state)
{
    state->positions[0].y += 1;
    int i, j;

    // General reset loop
    for (i = 0; i < state->max_entities; i++)
    {
        if (!state->entities[i])
        {
            continue;
        }

        state->colors[i].r = 0;
    }

    // Physics
    for (i = 0; i < state->max_entities; i++)
    {
        for (j = i; j < state->max_entities; j++)
        {
            // Skip same entities or inactive entities
            if (i == j || !state->entities[i] || !state->entities[j])
            {
                continue;
            }

            // Check if colliding; if so then highlight
            GManifold *manifold = NULL;
            if (gcollision_aabb(state->aabbs[i], state->positions[i], state->aabbs[j], state->positions[j], manifold))
            {
                state->colors[i].r = 255;
                state->colors[j].r = 255;
            }
        }
    }
}
