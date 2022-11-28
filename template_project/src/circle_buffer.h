#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Inspired by https://stackoverflow.com/a/827749

/// @brief A circular buffer.
typedef struct CircleBuffer
{
    /// @brief The data held in the buffer.
    void *buffer;
    /// @brief The end of the buffer.
    void *bufferEnd;
    /// @brief The capacity of the buffer.
    size_t capacity;
    /// @brief The number of active items in the buffer.
    size_t count;
    /// @brief The size of each item in the buffer.
    size_t itemSize;
    /// @brief The head of the queue.
    void *head;
    /// @brief The tail of the queue.
    void *tail;
} CircleBuffer;

/// @brief Creates a new circular buffer.
/// @param cb The pointer to the circular buffer.
/// @param capacity The capacity of the circular buffer.
/// @param itemSize The size of each item in the circular buffer.
/// @param onAllocError Calls a method if an error occured allocating.
/// @return Whether it was successfully able to create a buffer.
bool CircleBuffer_new(CircleBuffer *cb, size_t capacity, size_t itemSize);

/// @brief Frees the data of the circular buffer.
/// @param cb The buffer to free.
void CirclerBuffer_free(CircleBuffer *cb);

/// @brief Pushes an item on the end of the circle buffer.
/// @param cb The circle buffer to modify.
/// @param item The item to push onto the buffer.
/// @param onOverflowError A callback to call if the item would cause it to overflow.
void CircleBuffer_push_back(CircleBuffer *cb, const void *item, void (*onOverflowError)());

/// @brief Pops an item off the circle buffer.
/// @param cb The circle buffer to modify.
/// @param item The item to copy to.
/// @return Whether the pop was successful.
bool CircleBuffer_pop_front(CircleBuffer *cb, void *item);
