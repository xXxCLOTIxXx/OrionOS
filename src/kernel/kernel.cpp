#include "kernel_io/stdio.cpp"
#include "kernel_io/stdtimers.cpp"


extern "C" void kernel_main() {
    print("Starting kernel...");
    endl();
    sleep(50);
    clear();
    print("VirtOs | alpha", Color::DarkCyan);
    while (1) {}
}
