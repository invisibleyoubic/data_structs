#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct ring_buffer {
    uint8_t *data;

    size_t capacity;
    size_t size;

    size_t write_ptr;
    size_t read_ptr;
} ring_buffer_t;

int ring_buffer_init(ring_buffer_t *buffer, uint8_t *data, size_t capacity);
size_t ring_buffer_size(const ring_buffer_t *buffer);
size_t ring_buffer_capacity(const ring_buffer_t *buffer);
bool ring_buffer_empty(const ring_buffer_t *buffer);
bool ring_buffer_full(const ring_buffer_t *buffer);
void ring_buffer_reset(ring_buffer_t *buffer);

int ring_buffer_write(ring_buffer_t *buffer, const void *input, size_t size);
int ring_buffer_read(ring_buffer_t *buffer, void *output, size_t size);
int ring_buffer_peek(const ring_buffer_t *buffer, void *output, size_t size);
