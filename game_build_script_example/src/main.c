#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include "vec2.h"
#include "game_state.h"

#ifndef TEST
int main()
{
    GameState *state = GameState_new();
    for (int i = 0; i < 10; i++)
    {
        GameState_tick(state);
    }

    return 0;
}

#endif
