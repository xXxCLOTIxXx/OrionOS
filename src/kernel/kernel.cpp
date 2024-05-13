//#include "kernel_io/stdio.cpp"
#include "kernel_io/stdtimers.cpp"
#include "utils/memory/memory_management.cpp"


extern "C" void kernel_main() {
    println("Starting kernel...");
    initialize_memory();
    sleep(20);
    clear();
    println("VirtOs | alpha", Color::DarkCyan);

    void* ptr = _kmalloc(100, 0);
    if (ptr == nullptr) {
        println("Failed to allocate memory!");
    } else{
        println("allocated memory: ");
        print_size_t((size_t)ptr);
    }
    //delete[] ptr;

    while (1) {}
}
