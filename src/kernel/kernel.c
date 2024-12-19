#include "kernel.h"
#include <include/keyboard.h>
#include <include/mem.h>
#include <lib/string.h>

#include <include/video/vbe.h>
#include <include/video/vbe_text.h>
#include "klog/log.h"

int kernel(multiboot_info_t* mbi) {
    printf("\nTOS kernel v0.1.6.7.12bt\n\n");
    
    //fill(RGB(0, 0, 0));

    // Инициализация памяти
    mem_info* inf = (mem_info*)kmalloc(sizeof(mem_info));
    if (!inf) {
        LOG_ERROR("Failed to allocate memory for mem_info.\n");
        return -1;
    }
    
    *inf = get_memory_info();
    LOG_OK("Total mem: %u", inf->total);
    LOG_OK("Free mem: %u", inf->free);
    LOG_OK("Used mem: %u", inf->used);


    while (1) { // Проверяем нажатие клавиши F11
        printf("{FG(194,122,255)}root#~ {FG(255,255,255)}");
        char* text = keyboard_input();
        printf("%c", '\n');

        
        if (strcmp(text, "clear") == 0){
            clear();
        } else if (strcmp(text, "reboot") == 0){
            return 1;
        }
}
}


