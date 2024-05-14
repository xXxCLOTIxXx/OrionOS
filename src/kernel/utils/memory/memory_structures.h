#ifndef MEMORY_STRUCTURES_H
#define MEMORY_STRUCTURES_H

#include <cstdint>
#include <cstddef>


struct _mem_block_t {
    size_t size;
    bool isFree;
    _mem_block_t* next;
};


struct {
    size_t used;
    size_t free;
    struct {
        void* addr;
        size_t length;
    } free_mem;
} system_memory;

#endif
