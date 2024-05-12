// kernel.cpp
extern "C" void kernel_main() {
    const char* hello = "VirtOS Alpha | Hello world from VirtOS!";
    volatile unsigned char* video_memory = (volatile unsigned char*) 0xb8000;
    for (int i = 0; hello[i] != '\0'; ++i) {
        video_memory[i * 2] = hello[i];
        video_memory[i * 2 + 1] = 0x0F;  // Белый текст на черном фоне
    }

    // Бесконечный цикл, чтобы остановить выполнение ядра
    while (1) {}
}
