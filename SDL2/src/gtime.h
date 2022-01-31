#include <stdint.h>
#include <time.h>

#define NANOS_IN_SECOND 1000000000.0

// An instant in time.
typedef struct GInstant
{
    struct timespec instant;
} GInstant;

// Returns the current instant.
GInstant gnow()
{
    struct timespec start;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    struct GInstant c;
    c.instant = start;

    return c;
}

// Returns the elapsed seconds.
double gdelta_t(struct GInstant newest, struct GInstant oldest)
{
    // Convert instants to nanos
    double d_newest = (double)newest.instant.tv_sec * NANOS_IN_SECOND + (double)newest.instant.tv_nsec;
    double d_oldest = (double)oldest.instant.tv_sec * NANOS_IN_SECOND + (double)oldest.instant.tv_nsec;

    double nanos = d_newest - d_oldest;

    // Prevent a negative value from being returned
    if (nanos < 0.)
    {
        return 0.;
    }

    // Convert to seconds
    double seconds = nanos / NANOS_IN_SECOND;

    return seconds;
}