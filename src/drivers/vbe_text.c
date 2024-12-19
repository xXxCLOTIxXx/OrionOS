#include <include/video/vbe_text.h>
#include <include/res/font.h>

uint16_t xpos = 0;
uint16_t ypos = 0;
uint32_t bg_color = 0;
uint32_t fg_color = RGB(255, 255, 255);


void vbe_bitmapblt(
    uint16_t x, 
    uint16_t y,
    uint8_t h,
    uint8_t* bitpattern,
    uint32_t fore_color,
    uint32_t back_color
    )
{
    uint16_t xx;

    uint16_t yy = y;
    for (uint32_t j = 0; j < h; j++) {

        xx = x;
        for (uint32_t i = 128; i > 0; i >>= 1)
        {

            if (i & *bitpattern)
                vbe_set_pixel(xx, yy, fore_color);
            else 
                vbe_set_pixel(xx, yy, back_color);

            xx++;
        }

        bitpattern++;
        yy++;
    }
}

void vbe_drawchar_at_pos(
    char c,
    uint16_t x, 
    uint16_t y,
    uint32_t fore_color,
    uint32_t back_color
    )
{
    vbe_bitmapblt(x, y, 13, &FontData[(uint32_t)c * 13], fore_color, back_color);
}


void vbe_putchar(char c) {
    if (c == '\n') {
        xpos = 0;
        ypos+=14;
    } else if (c == '\r') {
        xpos = 0;
    } else {
        vbe_drawchar_at_pos(c, xpos, ypos, fg_color, bg_color);
        xpos+=8;
        if (xpos >= screen_width) {
            xpos = 0;
            ypos+=14;
        }
    }
}


void vbe_text_print(const char* str, uint16_t x, uint16_t y, uint32_t fore_color, uint32_t back_color) {
    while (*str != '\0') {
        vbe_drawchar_at_pos(*str, x, y, fore_color, back_color);  // Рисуем каждый символ
        x += 8;  // Сдвиг по горизонтали на 8 пикселей (ширина символа)
        str++;    // Переходим к следующему символу
    }
}

void printf(const char *format, ...) {
    char **arg = (char **) &format;
    int c;
    char buf[20];

    arg++;  // Указатель на первый аргумент

    while ((c = *format++) != '\0') {
        if (c == '{' && strncmp(format, "BG(", 3) == 0) {
            // Парсинг цвета BG
            format += 3;  // Пропускаем "BG("
            int r = 0, g = 0, b = 0;

            // Читаем числа вручную
            r = 0;
            while (*format >= '0' && *format <= '9') {
                r = r * 10 + (*format - '0');
                format++;
            }

            if (*format == ',') format++;  // Пропускаем запятую

            g = 0;
            while (*format >= '0' && *format <= '9') {
                g = g * 10 + (*format - '0');
                format++;
            }

            if (*format == ',') format++;  // Пропускаем запятую

            b = 0;
            while (*format >= '0' && *format <= '9') {
                b = b * 10 + (*format - '0');
                format++;
            }

            if (*format == ')') format++;  // Пропускаем ')'
            if (*format == '}') format++;  // Пропускаем '}'

            bg_color = RGB(r, g, b);  // Устанавливаем цвет фона
        } else if (c == '{' && strncmp(format, "FG(", 3) == 0) {
            // Парсинг цвета FG
            format += 3;  // Пропускаем "FG("
            int r = 0, g = 0, b = 0;

            // Читаем числа вручную
            r = 0;
            while (*format >= '0' && *format <= '9') {
                r = r * 10 + (*format - '0');
                format++;
            }

            if (*format == ',') format++;  // Пропускаем запятую

            g = 0;
            while (*format >= '0' && *format <= '9') {
                g = g * 10 + (*format - '0');
                format++;
            }

            if (*format == ',') format++;  // Пропускаем запятую

            b = 0;
            while (*format >= '0' && *format <= '9') {
                b = b * 10 + (*format - '0');
                format++;
            }

            if (*format == ')') format++;  // Пропускаем ')'
            if (*format == '}') format++;  // Пропускаем '}'

            fg_color = RGB(r, g, b);  // Устанавливаем цвет текста
        } else if (c != '%') {
            vbe_putchar(c);  // Просто выводим символ
        } else {
            // Обработка форматов
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
                    itoa(buf, c, *((int *) arg++));  // Преобразуем число в строку
                    p = buf;
                    goto string;
                    break;
                case 'c': {
                    char char_value = (char) *((int *) arg++);
                    for (int i = 0; i < pad - 1; i++) vbe_putchar(' ');
                    vbe_putchar(char_value);
                    break;
                }
                case 's':
                    p = *arg++;
                    if (!p) {
                        p = "(null)";
                    }

                string:
                    // Добавление паддинга для строк
                    for (p2 = p; *p2; p2++);
                    for (; p2 < p + pad; p2++) 
                        vbe_putchar(' ');  // Паддинг пробелами
                    while (*p) 
                        vbe_putchar(*p++);  // Выводим символы строки
                    break;

                default:
                    vbe_putchar(c);  // Простой вывод символа
                    break;
            }
        }
    }
}




void fill(uint32_t color) {
    uint16_t width = screen_width;
    uint16_t height = screen_height;

    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            vbe_set_pixel(x, y, color);  // Устанавливаем цвет фона для каждого пикселя
        }
    }
    xpos=0;
    ypos=0;
}

void clear(){
    fill(0);
}







