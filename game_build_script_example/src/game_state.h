#pragma once
#include "vec2.h"

#define NUM_POSITIONS 1000

/// @brief The game state for a game. Allocates everything at once.
typedef struct GameState
{
    Vec2 *positions;
    Vec2 *prev_positions;
} GameState;

/// @brief Ticks the given game state.
/// @param state
void GameState_tick(GameState *state);

/// @brief Creates a new game state.
/// @return
GameState *GameState_new();

/// @brief Deletes the given state.
/// @param state
void GameState_delete(GameState *state);
