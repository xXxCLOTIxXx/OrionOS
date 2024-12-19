#ifndef VBE_DRIVER_H
#define VBE_DRIVER_H

#include <lib/types.h>
#include <include/multiboot.h>

// Цветовые макросы
#define RGB(r, g, b)       ((uint32_t)(((r) << 16) | ((g) << 8) | (b)))
#define RGBA(r, g, b, a)   ((uint32_t)(((r) << 16) | ((g) << 8) | (b) | ((a) << 24)))

// Доступ к отдельным компонентам цвета
#define R_PART(color) (((color) >> 16) & 0xFF)
#define G_PART(color) (((color) >> 8) & 0xFF)
#define B_PART(color) ((color) & 0xFF)
#define A_PART(color) (((color) >> 24) & 0xFF)

// Структуры
typedef struct {
    uint16_t x, y; // Координаты пикселя
} Point;

typedef struct {
    uint16_t x1, y1; // Верхний левый угол
    uint16_t x2, y2; // Нижний правый угол
} Rectangle;

typedef uint32_t Color;

// Экспортируемые переменные
extern uint32_t* framebuffer;
extern uint32_t screen_width;
extern uint32_t screen_height;
extern uint32_t screen_pitch;
extern uint8_t screen_bpp;

// Функции
void vbe_init(multiboot_info_t* mbi);
void vbe_set_pixel(uint16_t x, uint16_t y, Color color);
Color vbe_get_pixel(uint16_t x, uint16_t y);

#endif // VBE_DRIVER_H
