#include <include/keyboard.h>
#include <include/io.h> // Для работы с портами
#include <stddef.h>
#include <stdbool.h>
#include <include/video/vbe_text.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

static char input_buffer[256]; // Буфер для строки
static uint8_t buffer_index = 0;
static bool shift_pressed = false;

// Keymaps

// Таблицы сканкодов
unsigned char keymap[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    19,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    18,	/* Left Arrow */
    0,
    17,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    20,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char keymap_up[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '{', '}', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ':',	/* 39 */
 '\"', '~',   0,		/* Left shift */
 '|', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', '<', '>', '?',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    19,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    18,	/* Left Arrow */
    0,
    17,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    20,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

// Инициализация клавиатуры
void keyboard_init(void) {
    // Здесь можно включить прерывания клавиатуры, если используются
}

// Проверка состояния клавиши (нажата/не нажата)
bool keyboard_key(uint8_t keycode) {
    uint8_t status = inb(KEYBOARD_STATUS_PORT);
    if (status & 0x01) { // Проверка, есть ли данные
        uint8_t scan_code = inb(KEYBOARD_DATA_PORT);

        // Обработка нажатий клавиш Shift
        if (scan_code == 0x2A || scan_code == 0x36) {
            shift_pressed = true;
        } else if (scan_code == 0xAA || scan_code == 0xB6) {
            shift_pressed = false;
        }

        // Вернуть true, если скан-код совпадает с нужным
        if (scan_code == keycode) {
            return true;
        }
    }
    return false;
}

// Получение строки текста с клавиатуры
char* keyboard_input(void) {
    while (1) {
        uint8_t status = inb(KEYBOARD_STATUS_PORT);
        if (status & 0x01) { // Если есть данные
            uint8_t scan_code = inb(KEYBOARD_DATA_PORT);

            // Если клавиша отпущена, пропускаем
            if (scan_code & 0x80) continue;

            char c = shift_pressed ? keymap_up[scan_code] : keymap[scan_code];

            // Если нажата Enter, завершить ввод
            if (c == '\n') {
                input_buffer[buffer_index] = '\0';
                buffer_index = 0; // Сброс индекса для следующей строки
                return input_buffer;
            }

            // Добавляем символ в буфер
            if (buffer_index < sizeof(input_buffer) - 1) {
                input_buffer[buffer_index++] = c;
                printf("%c", c);
            }
        }
    }
}
