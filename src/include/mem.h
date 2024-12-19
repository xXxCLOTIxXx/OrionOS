#ifndef MEM_H
#define MEM_H


#include <include/multiboot.h>
#include <lib/types.h>

#define true 1
#define false 0

typedef struct MemoryBlock {
    uint32_t base_addr;
    uint32_t length;
    int free;
    struct MemoryBlock* next;
} mem_block;

typedef struct MemoryInfo {
    uint32_t total;
    uint32_t used;
    uint32_t free;
} mem_info;


int mem_init(multiboot_info_t* mbi);
mem_info get_memory_info();
int get_free_memory();
int get_used_memory();
int get_total_memory();


void* kmalloc(size_t size);
void kfree(void* ptr);


extern mem_block* memory_map;
extern mem_block* first_free_block;

#endif
