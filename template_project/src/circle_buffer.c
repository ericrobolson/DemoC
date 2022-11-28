#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "circle_buffer.h"

/// @brief Creates a new circular buffer.
/// @param cb The pointer to the circular buffer.
/// @param capacity The capacity of the circular buffer.
/// @param itemSize The size of each item in the circular buffer.
bool CircleBuffer_new(CircleBuffer *cb, size_t capacity, size_t itemSize)
{
    bool successfulInitialization = true;
    cb->buffer = malloc(capacity * itemSize);

    // Handle any errors.
    if (cb->buffer == NULL)
    {
        cb->bufferEnd = (char *)cb->buffer + capacity + itemSize;
        successfulInitialization = false;
    }

    cb->capacity = capacity;
    cb->count = 0;
    cb->itemSize = itemSize;
    cb->head = cb->buffer;
    cb->tail = cb->buffer;

    return successfulInitialization;
}

/// @brief Frees the data of the circular buffer.
/// @param cb The buffer to free.
void CirclerBuffer_free(CircleBuffer *cb)
{
    free(cb->buffer);
    cb->capacity = 0;
    cb->count = 0;
    cb->itemSize = 0;
    cb->head = NULL;
    cb->tail = NULL;
}

/// @brief Pushes an item on the end of the circle buffer.
/// @param cb The circle buffer to modify.
/// @param item The item to push onto the buffer.
/// @param onOverflowError A callback to call if the item would cause it to overflow.
void CircleBuffer_push_back(CircleBuffer *cb, const void *item, void (*onOverflowError)())
{
    if (cb->count == cb->capacity)
    {
        onOverflowError();
    }
    else
    {
        memcpy(cb->head, item, cb->itemSize);
        cb->head = (char *)cb->head + cb->itemSize;
        if (cb->head == cb->bufferEnd)
        {
            cb->head = cb->buffer;
        }
        cb->count += 1;
    }
}

/// @brief Pops an item off the circle buffer.
/// @param cb The circle buffer to modify.
/// @param item The item to copy to.
/// @return Whether the pop was successful.
bool CircleBuffer_pop_front(CircleBuffer *cb, void *item)
{
    bool hasError = false;
    if (cb->count == 0)
    {
        hasError = true;
    }
    else
    {
        memcpy(item, cb->tail, cb->itemSize);
        cb->tail = (char *)cb->tail + cb->itemSize;
        if (cb->tail == cb->bufferEnd)
        {
            cb->tail = cb->buffer;
        }
        cb->count -= 1;
    }

    return hasError;
}
