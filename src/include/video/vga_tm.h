#ifndef VGA_TM_H
#define VGA_TM_H


#define COLUMNS 80
#define ROWS 25
#define VIDEO_ADDRESS 0xB8000
#define ATTRIBUTE 0x07



void tm_vga_clear(void);
void tm_vga_putchar(int c);
void tm_vga_printf(const char *format, ...);
void tm_vga_update_cursor(int x, int y);

#endif