#include <include/video/vga_tm.h>
#include <include/io.h>
#include <lib/types.h>
#include <lib/string.h>



static volatile uint16_t *video = (uint16_t *)VIDEO_ADDRESS;


static int xpos = 0;
static int ypos = 0;


static void tm_vga_put_char_at(char c, int x, int y, uint8_t attr) {
    video[y * COLUMNS + x] = (attr << 8) | c;
}


void tm_vga_clear(void) {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLUMNS; x++) {
            tm_vga_put_char_at(' ', x, y, ATTRIBUTE);
        }
    }
    xpos = 0;
    ypos = 0;
}


void tm_vga_update_cursor(int x, int y) {
    uint16_t pos = y * COLUMNS + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}


void tm_vga_putchar(int c) {
    if (c == '\n') {
        xpos = 0;
        ypos++;
    } else if (c == '\r') {
        xpos = 0;
    } else {
        tm_vga_put_char_at(c, xpos, ypos, ATTRIBUTE);
        xpos++;
        if (xpos >= COLUMNS) {
            xpos = 0;
            ypos++;
        }
    }

    if (ypos >= ROWS) {

        for (int y = 1; y < ROWS; y++) {
            for (int x = 0; x < COLUMNS; x++) {
                video[(y - 1) * COLUMNS + x] = video[y * COLUMNS + x];
            }
        }
 
        for (int x = 0; x < COLUMNS; x++) {
            tm_vga_put_char_at(' ', x, ROWS - 1, ATTRIBUTE);
        }
        ypos = ROWS - 1;
    }

    tm_vga_update_cursor(xpos, ypos);
}

void tm_vga_puts(const char *str) {
    while (*str) {
        tm_vga_putchar(*str++);
    }
}


void tm_vga_printf(const char *format, ...) {
    char **arg = (char **) &format;
    int c;
    char buf[20];

    arg++;

    while ((c = *format++) != 0) {
        if (c != '%') {
            tm_vga_putchar(c);
        } else {
            char *p, *p2;
            int pad0 = 0, pad = 0;

            c = *format++;
            if (c == '0') {
                pad0 = 1;
                c = *format++;
            }

            if (c >= '0' && c <= '9') {
                pad = c - '0';
                c = *format++;
            }

            switch (c) {
            case 'd':
            case 'u':
            case 'x':
                itoa(buf, c, *((int *) arg++));
                p = buf;
                goto string;
                break;

            case 's':
                p = *arg++;
                if (!p) {
                    p = "(null)";
                }

            string:
                for (p2 = p; *p2; p2++);
                for (; p2 < p + pad; p2++)
                    tm_vga_putchar(pad0 ? '0' : ' ');
                while (*p)
                    tm_vga_putchar(*p++);
                break;

            default:
                tm_vga_putchar(*((int *) arg++));
                break;
            }
        }
    }
}



