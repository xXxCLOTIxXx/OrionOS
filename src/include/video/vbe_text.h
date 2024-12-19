#ifndef VBE_TEXT_H
#define VBE_TEXT_H

#include <stdint.h>
#include <include/video/vbe.h>
#include <lib/string.h>

void vbe_bitmapblt(
    uint16_t x, 
    uint16_t y,
    uint8_t h,
    uint8_t* bitpattern,
    uint32_t fore_color,
    uint32_t back_color
    );

void vbe_drawchar_at_pos(
    char c,
    uint16_t x, 
    uint16_t y,
    uint32_t fore_color,
    uint32_t back_color
    );

void vbe_putchar(char c);

void vbe_text_print(const char* str, uint16_t x, uint16_t y, uint32_t fore_color, uint32_t back_color);

void printf(const char *format, ...);



void fill(uint32_t color);
void clear();


#endif // VBE_TEXT_H
