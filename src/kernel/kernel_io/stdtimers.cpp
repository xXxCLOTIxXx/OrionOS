#include <chrono>
#include <thread>


void sleep(uint32_t milliseconds) {
    uint32_t iterations = milliseconds*5;
    for (uint32_t i = 0; i < iterations; ++i) {
        asm volatile(
			"mov $1000000, %ecx\n"
			"1:\n"
			"rep nop\n"
			"loop 1b\n"

        );
    }
}
