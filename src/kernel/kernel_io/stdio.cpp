#include <stddef.h>
#include <stdint.h>
#include "colors.h"

#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define LINES 25
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

extern "C" volatile unsigned char* video_memory = (volatile unsigned char*)0xb8000;
size_t current_loc = 0;


void size_t_to_char(size_t num, char* result) {
    // Преобразование числа в строку
    size_t temp = num;
    int digit_count = 0;
    do {
        ++digit_count;
        temp /= 10;
    } while (temp > 0);

    temp = num;
    for (int i = digit_count - 1; i >= 0; --i) {
        result[i] = '0' + temp % 10;
        temp /= 10;
    }
    result[digit_count] = '\0'; // Завершающий символ строки
}


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

void println(const char* message, uint8_t color = Color::White){
    print(message, color);
    endl();
}

void print_size_t(size_t num, uint8_t color = Color::White) {
    char buffer[20]; // Размер буфера зависит от максимального числа символов в представлении size_t
    size_t_to_char(num, buffer); // Предполагается, что у вас есть функция size_t_to_char, как в предыдущем примере
    println(buffer, color);
}