#include "base_io/stdio.cpp"
#include "base_io/stdtimers.cpp"
#include "utils/multiboot.h"

#include "utils/memory/memory_management.cpp"

void loop() {
    while (true) {}
}

extern "C" void kernel_main(multiboot_info_t *multiboot) {
    println("Starting the system...");
    if (multiboot == nullptr) {
        println("memory info is empty! FATAL ERROR", Color::LightRed);
        loop();
    }
    init_system_memory(multiboot->mmap_length, (void*)multiboot->mmap_addr, multiboot->mmap_length);
    print("Successful memory initialization: ", Color::DarkGreen);
    print_size_t(multiboot->mmap_length);
    endl();

    sleep(55);
    clear();
    println("Welcome to OrionOS.", Color::LightCyan);
    void* mem = _kmalloc(100, 0);
    if (mem != nullptr) {
        print("Memory allocated successfully: ", Color::DarkGreen);
        print_size_t(reinterpret_cast<size_t>(mem));
    } else {
        println("Memory allocation test failed.", Color::DarkRed);
    }

    loop();
}