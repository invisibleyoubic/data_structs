#include <stdint.h>

#include "ring_buffer.h"

int main(void) {
    uint8_t data[10] = {0};
    ring_buffer_t ring_buffer;

    ring_buffer_init(&ring_buffer, data, sizeof(data));

    uint8_t input1[8] = {8, 1, 2, 3, 4, 5, 6, 7};
    ring_buffer_write(&ring_buffer, input1, sizeof(input1));

    uint8_t output1[8];
    ring_buffer_read(&ring_buffer, output1, sizeof(output1));

    char input2[5] = {'a', 'b', 'c', 'd', 'e'};
    ring_buffer_write(&ring_buffer, input2, sizeof(input2));

    uint8_t output2[2];
    ring_buffer_read(&ring_buffer, output2, sizeof(output2));

    uint8_t output3[10];
    ring_buffer_read(&ring_buffer, output3, 3);

    return 0;
}
