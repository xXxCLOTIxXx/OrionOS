#include <include/video/vbe.h>

// Глобальные переменные для видеопамяти
uint32_t* framebuffer = NULL;
uint32_t screen_width = 0;
uint32_t screen_height = 0;
uint32_t screen_pitch = 0;
uint8_t screen_bpp = 0;

// Инициализация VBE
void vbe_init(multiboot_info_t* mbi) {
    framebuffer = (uint32_t*)(uint32_t)mbi->framebuffer_addr;
    screen_pitch = mbi->framebuffer_pitch;
    screen_width = mbi->framebuffer_width;
    screen_height = mbi->framebuffer_height;
    screen_bpp = mbi->framebuffer_bpp;
}

// Установка пикселя
void vbe_set_pixel(uint16_t x, uint16_t y, Color color) {
    if (x >= screen_width || y >= screen_height || framebuffer == NULL) {
        return; // Защита от выхода за границы
    }
    framebuffer[y * (screen_pitch / 4) + x] = color; // Используем деление на 4 для 32-битного режима
}

// Получение цвета пикселя
Color vbe_get_pixel(uint16_t x, uint16_t y) {
    if (x >= screen_width || y >= screen_height || framebuffer == NULL) {
        return 0; // Возвращаем чёрный цвет при ошибке
    }
    return framebuffer[y * (screen_pitch / 4) + x];
}