#include <include/mem.h>

// Глобальные переменные
mem_block* memory_map = NULL;
mem_block* first_free_block = NULL;


void add_memory_region(uint32_t base_addr, uint32_t length, int free) {
    mem_block* new_block = (mem_block*)base_addr;
    if (!new_block) return;

    new_block->base_addr = base_addr;
    new_block->length = length;
    new_block->free = free;
    new_block->next = NULL;

    if (!memory_map) {
        memory_map = new_block;
        first_free_block = new_block;
    } else {
        mem_block* current = memory_map;
        while (current->next) {
            current = current->next;
        }
        current->next = new_block;
    }
}


int mem_init(multiboot_info_t* mbi) {
    if (mbi->flags & (1 << 6)) {
        multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)mbi->mmap_addr;
        uint32_t mmap_end = mbi->mmap_addr + mbi->mmap_length;

        while ((uint32_t)mmap < mmap_end) {
            if (mmap->type == 1) { 
                add_memory_region((uint32_t)mmap->addr, (uint32_t)mmap->len, true);
            }
            mmap = (multiboot_memory_map_t*)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
        }
        return true;
    }
    return false;
}


mem_info get_memory_info() {
    mem_info inf = {0, 0, 0};

    mem_block* current = memory_map;
    while (current) {
        if (current->free) {
            inf.free += current->length;
        } else {
            inf.used += current->length;
        }
        current = current->next;
    }
    inf.total = inf.free + inf.used;
    return inf;
}

int get_free_memory() {
    return get_memory_info().free;
}

int get_used_memory() {
    return get_memory_info().used;
}

int get_total_memory() {
    return get_memory_info().total;
}


void* kmalloc(size_t size) {
    mem_block* current = first_free_block;

    while (current) {
        if (current->free && current->length >= size) {
            current->free = false;

            if (current->length > size + sizeof(mem_block)) {
                
                mem_block* new_block = (mem_block*)((uint32_t)current + size);
                new_block->base_addr = current->base_addr + size;
                new_block->length = current->length - size;
                new_block->free = true;
                new_block->next = current->next;

                current->length = size;
                current->next = new_block;
            }

            return (void*)((uint32_t)current + sizeof(mem_block));
        }
        current = current->next;
    }

    return NULL;
}



void kfree(void* ptr) {
    mem_block* block = (mem_block*)((uint32_t)ptr - sizeof(mem_block));
    block->free = true;
    mem_block* current = memory_map;
    while (current) {
        if (current->free && current->next && current->next->free) {
            current->length += current->next->length;
            current->next = current->next->next;
        }
        current = current->next;
    }




}
