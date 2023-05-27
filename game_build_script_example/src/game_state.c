#include <stdlib.h>
#include "game_state.h"
#include <assert.h>
#include <stdio.h>

void check_physics(GameState state)
{
    for (int i = 0; i < 10; i++)
    {
        Vec2_print(state.positions[i]);
    }
    printf("\n");
}

void GameState_tick(GameState *state)
{
    assert(state != NULL);

    for (int i = 0; i < NUM_POSITIONS; i++)
    {
        state->prev_positions[i] = state->positions[i];
        state->positions[i].x += 1;
    }

    check_physics(*state);
}

GameState *GameState_new()
{
    GameState *state = malloc(sizeof(GameState));
    if (state != NULL)
    {
        // Allocate
        state->positions = malloc(NUM_POSITIONS * sizeof(Vec2));
        assert(state->positions != NULL);
        state->prev_positions = malloc(NUM_POSITIONS * sizeof(Vec2));
        assert(state->prev_positions != NULL);
    }

    return state;
}

void GameState_delete(GameState *state)
{
    if (state != NULL)
    {
        free(state);
    }
}
