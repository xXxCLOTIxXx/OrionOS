#include "log.h"
#include <include/video/vbe_text.h>
#include <lib/string.h>


void LOG_OK(const char *format, ...) {
    printf("[ {FG(0,255,0)}OK{FG(255,255,255)} ] ");  // Префикс с цветами

    va_list args;  // Для обработки переменного числа аргументов
    va_start(args, format);

    char buffer[256];  // Временный буфер для форматированной строки
    vsnprintf(buffer, sizeof(buffer), format, args);  // Форматируем строку

    printf("%s\n", buffer);  // Выводим форматированное сообщение

    va_end(args);  // Завершаем работу с va_list
}


void LOG_INFO(const char *format, ...){

    printf("[ {FG(0,0,255)}INFO{FG(255,255,255)} ] ");  // Префикс с цветами

    va_list args;  // Для обработки переменного числа аргументов
    va_start(args, format);

    char buffer[256];  // Временный буфер для форматированной строки
    vsnprintf(buffer, sizeof(buffer), format, args);  // Форматируем строку

    printf("%s\n", buffer);  // Выводим форматированное сообщение

    va_end(args);  // Завершаем работу с va_list

}
void LOG_WARNING(const char *format, ...){

    printf("[ {FG(255,255,0)}WARNING{FG(255,255,255)} ] ");  // Префикс с цветами

    va_list args;  // Для обработки переменного числа аргументов
    va_start(args, format);

    char buffer[256];  // Временный буфер для форматированной строки
    vsnprintf(buffer, sizeof(buffer), format, args);  // Форматируем строку

    printf("%s\n", buffer);  // Выводим форматированное сообщение

    va_end(args);  // Завершаем работу с va_list

}
void LOG_ERROR(const char *format, ...){

    printf("[ {FG(255,0,0)}ERROR{FG(255,255,255)} ] ");  // Префикс с цветами

    va_list args;  // Для обработки переменного числа аргументов
    va_start(args, format);

    char buffer[256];  // Временный буфер для форматированной строки
    vsnprintf(buffer, sizeof(buffer), format, args);  // Форматируем строку

    printf("%s\n", buffer);  // Выводим форматированное сообщение

    va_end(args);  // Завершаем работу с va_list

}
void PANIC(const char *format, ...){

    printf("{BG(255,0,0)}[ PANIC ] ");  // Префикс с цветами

    va_list args;  // Для обработки переменного числа аргументов
    va_start(args, format);

    char buffer[256];  // Временный буфер для форматированной строки
    vsnprintf(buffer, sizeof(buffer), format, args);  // Форматируем строку

    printf("%s\n", buffer);  // Выводим форматированное сообщение
    printf("{BG(0,0,0)}");

    va_end(args);  // Завершаем работу с va_list
}