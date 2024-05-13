#ifndef MEMORY_STRUCTURES_H
#define MEMORY_STRUCTURES_H

#include <cstdint>
#include <cstddef>


// Структура для представления блока памяти
struct _mem_block_t {
    size_t size; // Размер блока памяти
    uint8_t isFree; // Флаг, указывающий, свободен ли блок памяти
    _mem_block_t* next; // Указатель на следующий блок памяти
};

// Глобальная структура для управления памятью
struct {
    size_t used; // Использованное пространство памяти
    size_t constfree; // Общее количество свободной памяти
    struct {
        void* addr; // Адрес начала свободной памяти
        size_t length; // Длина свободной памяти
    } free_mem;
} system_memory;

#endif // MEMORY_STRUCTURES_H
