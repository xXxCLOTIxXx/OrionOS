#include <stddef.h>
#include <stdint.h>
#include "colors.h"

#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define LINES 25
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

extern "C" volatile unsigned char* video_memory = (volatile unsigned char*)0xb8000;
size_t current_loc = 0;


void print(const char* message, uint8_t color = Color::White) {
    for (int i = 0; message[i] != '\0'; ++i) {
        video_memory[current_loc] = message[i];
        video_memory[current_loc + 1] = color;
        current_loc += BYTES_FOR_EACH_ELEMENT;
    }
}


void endl() {
    size_t line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
    size_t remainder = line_size - (current_loc % line_size);

    if (remainder != line_size) {
        current_loc += remainder;
    }
}


void clear() {
    for (unsigned int i = 0; i < SCREENSIZE; i += BYTES_FOR_EACH_ELEMENT) {
        video_memory[i] = ' ';
        video_memory[i + 1] = 0x07;
    }
    current_loc = 0;
}