#include "memory_structures.h"
#include <cstdint>

_mem_block_t* kMemStart_mem_block = nullptr;

void init_system_memory(size_t initial_free, void* initial_addr, size_t initial_length) {
    system_memory.used = 0;
    system_memory.free = initial_free;
    system_memory.free_mem.addr = initial_addr;
    system_memory.free_mem.length = initial_length;
}






void* _kmalloc(size_t size, uint32_t aligned) {
    if (size == 0) {
        return nullptr;
    }

    size_t total_size = size + sizeof(_mem_block_t);

    if(system_memory.free - system_memory.used <= size || system_memory.free - system_memory.used <= total_size) {
        // Обработка ситуации, когда памяти недостаточно
        return nullptr;
    } else if(kMemStart_mem_block == nullptr) {
        // Инициализация блока памяти, если он еще не был инициализирован
        kMemStart_mem_block = (_mem_block_t*)((uint32_t)system_memory.free_mem.addr);
        system_memory.used = 0;
        kMemStart_mem_block->size = system_memory.free_mem.length - sizeof(_mem_block_t);
        kMemStart_mem_block->isFree = 1;
        kMemStart_mem_block->next = nullptr;
    }

    _mem_block_t* current_mem_block = kMemStart_mem_block;
    _mem_block_t* prev_mem_block = nullptr;
    _mem_block_t* startedAt = current_mem_block;
    while (1) {
        if (current_mem_block == nullptr) return nullptr;
        if (current_mem_block->isFree && current_mem_block->size >= size) {
            // Найден свободный блок памяти нужного размера
            current_mem_block->isFree = 0;
            if (current_mem_block->next == nullptr) {
                // Если остаточная память в блоке достаточно большая, чтобы разделить его на два блока
                current_mem_block->next = (_mem_block_t*)((char*)current_mem_block + size + sizeof(_mem_block_t));
                current_mem_block->next->size = current_mem_block->size - sizeof(_mem_block_t) - size;
                current_mem_block->next->isFree = 1;
                current_mem_block->next->next = nullptr;
            }
            current_mem_block->size = size;
            system_memory.used += total_size;
            return (char*)current_mem_block + sizeof(_mem_block_t);
        } 
        prev_mem_block = current_mem_block;
        current_mem_block = current_mem_block->next;

        // нужно тестировать короче... ыы
    }
    return nullptr;
}
