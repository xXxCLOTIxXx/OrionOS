nasm -f elf32 src/kernel/boot.asm -o kasm.o #компилируем загрузчик
gcc -fno-stack-protector -m32 -c src/kernel/kernel.cpp -o kmain.o #компилируем ядро
ld -m elf_i386 -T linker.ld -o kernel kasm.o kmain.o #линкуем их
rm kasm.o kmain.o #удаляем временные файлы
mv kernel build/boot/kernel.bin #переносим наш слинкованый файл в папку с настройками grub
grub-mkrescue -o build.iso build #создаем образ диска
rm build/boot/kernel.bin #build/boot/kernel.img #удаляем файлы в папке с настройками grub
