#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

void keyboard_init(void);

// Проверка состояния клавиши (нажата/не нажата)
bool keyboard_key(uint8_t keycode);

// Получение строки текста с клавиатуры
char* keyboard_input(void);

#endif // KEYBOARD_H
