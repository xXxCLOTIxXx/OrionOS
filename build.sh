nasm -f elf32 src/kernel/boot.asm -o kasm.o
gcc -fno-stack-protector -m32 -c src/kernel/kernel.cpp -o kmain.o
ld -m elf_i386 -T linker.ld -o kernel kasm.o kmain.o
rm kasm.o kmain.o
mv kernel build/boot/kernel.bin
grub-mkrescue -o build.iso build
rm build/boot/kernel.bin #build/boot/kernel.img
