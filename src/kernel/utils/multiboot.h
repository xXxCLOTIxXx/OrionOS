#include <cstdint>

struct multiboot_info {
    uint32_t mmap_length;
    uint32_t mmap_addr;
};
typedef struct multiboot_info multiboot_info_t;
