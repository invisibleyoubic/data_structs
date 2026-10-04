#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ring_buffer.h"

inline static size_t ring_buffer_next_pos(const ring_buffer_t *buffer, size_t current, size_t size) {
    return (current + size) % buffer->capacity;
}

int ring_buffer_init(ring_buffer_t *buffer, uint8_t *data, size_t capacity) {
    if (buffer == NULL || data == NULL)
        return -1;

    buffer->data = data;
    buffer->capacity = capacity;
    buffer->size = 0;
    buffer->read_ptr = 0;
    buffer->write_ptr = 0;

    return 0;
}

size_t ring_buffer_size(const ring_buffer_t *buffer)
{
    return buffer->size;
}

size_t ring_buffer_capacity(const ring_buffer_t *buffer)
{
    return buffer->capacity;
}

bool ring_buffer_empty(const ring_buffer_t *buffer)
{
    return buffer->size == 0;
}

bool ring_buffer_full(const ring_buffer_t *buffer)
{
    return buffer->capacity == buffer->size;
}

void ring_buffer_reset(ring_buffer_t *buffer)
{
    buffer->write_ptr = 0;
    buffer->read_ptr = 0;
    buffer->size = 0;
    memset(buffer->data, 0, buffer->capacity);
}

int ring_buffer_write(ring_buffer_t *buffer, const void *input, size_t size) {
    if (buffer == NULL || input == NULL)
        return -1;
    if (size > buffer->capacity)
        return -1;

    const uint8_t *src = input;
    for (size_t i = 0; i < size; ++i)
    {
        buffer->data[buffer->write_ptr] = src[i];
        buffer->write_ptr = ring_buffer_next_pos(buffer, buffer->write_ptr, 1);

        if (buffer->size == buffer->capacity)
            buffer->read_ptr = ring_buffer_next_pos(buffer, buffer->read_ptr, 1);
        else
            buffer->size++;
    }
    return 0;
}

int ring_buffer_read(ring_buffer_t *buffer, void *output, size_t size) {
    if (buffer == NULL || output == NULL)
        return -1;
    if (size > buffer->size)
        return -1;
    
    uint8_t *dst = output;
    for (size_t i = 0; i < size; ++i)
    {
        dst[i] = buffer->data[buffer->read_ptr];
        buffer->read_ptr = ring_buffer_next_pos(buffer, buffer->read_ptr, 1);

        buffer->size--;
    }
    return 0;
}

int ring_buffer_peek(const ring_buffer_t *buffer, void *output, size_t size) {
    if (buffer == NULL || output == NULL)
        return -1;
    if (size > buffer->size)
        return -1;
    
    uint8_t *dst = output;
    size_t current = buffer->read_ptr;
    for (size_t i = 0; i < size; ++i)
    {
        dst[i] = buffer->data[current];
        current = ring_buffer_next_pos(buffer, current, 1);
    }
    return 0;
}
