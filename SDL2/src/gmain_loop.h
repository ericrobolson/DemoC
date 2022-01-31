#include "gtime.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>>
#include "gstate.h"

#define MAX_TICKS_PER_LOOP 10

// Render callback.
typedef void (*render_method)(GState, double);

// Poll events callback. Should return false if there was an error.
typedef bool (*poll_method)();

// The main loop of the app.
void gmain_loop(poll_method poll_events, render_method render)
{
    // Set up accumulator
    double accumulated_time = 0;
    double tick_hz = 1.0 / 60.0; // Tick at 60hz
    GInstant last_state_update = gnow();
    GInstant last_tick = gnow();
    GInstant now = gnow();
    int tick_counter = 0;

    // Misc vars
    bool should_exit = false;
    bool state_updated = false;
    uint64_t tick = 0;

    // Sim
    GState state = gstate_new();

    // Execute the loop
    while (!should_exit)
    {
        // First we need to poll events.
        if (poll_events() == false)
        {
            should_exit = true;
        }

        // While there's accumulated time, step the sim.
        // Limit to MAX_TICKS_PER_LOOP so we don't freeze here.
        state_updated = false;
        tick_counter = 0;
        while (accumulated_time > tick_hz && MAX_TICKS_PER_LOOP > tick_counter)
        {
            // Update accumulator + increment current sim executions
            accumulated_time -= tick_hz;
            state_updated = true;
            tick_counter += 1;

            // Perform the tick
            tick += 1;
            gtick_sim(&state);
            last_state_update = gnow();
        }

        // Trigger a render if the state was updated.
        if (state_updated)
        {
            render(state, gdelta_t(gnow(), last_state_update));
        }

        // Accumulate time
        now = gnow();
        accumulated_time += gdelta_t(now, last_tick);
        last_tick = now;
    }
}
