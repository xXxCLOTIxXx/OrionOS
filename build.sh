#!/bin/bash

SRC_DIR="src"
BUILD_DIR="build"


mkdir -p $BUILD_DIR


echo "Boot compiling..."
nasm -f elf32 -o $BUILD_DIR/boot.o $SRC_DIR/boot.asm


echo "Kernel compiling..."
gcc -I src -m32 -c -o $BUILD_DIR/kmain.o $SRC_DIR/kernel/kmain.c -std=gnu99 -ffreestanding -O2
gcc -I src -m32 -c -o $BUILD_DIR/kernel.o  $SRC_DIR/kernel/kernel.c -std=gnu99 -ffreestanding -O2



echo "Compiling drivers..."
for driver in $SRC_DIR/drivers/*.c; do
    driver_name=$(basename "$driver" .c)
    gcc -I src -m32 -c -o $BUILD_DIR/${driver_name}.o $driver -std=gnu99 -ffreestanding -O2
done

gcc -m32 -c -o $BUILD_DIR/string.o $SRC_DIR/lib/string.c -std=gnu99 -ffreestanding -O2
gcc -I src -m32 -c -o $BUILD_DIR/log.o $SRC_DIR/kernel/klog/log.c -std=gnu99 -ffreestanding -O2


echo "Linking..."
ld -m elf_i386 -T linker.ld -o $BUILD_DIR/kernel.elf $BUILD_DIR/*.o

echo "Building ISO..."
mkdir -p $BUILD_DIR/iso/boot/grub
cp $BUILD_DIR/kernel.elf $BUILD_DIR/iso/boot/kernel.elf
cp grub.cfg $BUILD_DIR/iso/boot/grub/grub.cfg
grub-mkrescue -o TOS.iso $BUILD_DIR/iso

# Запуск в QEMU
echo "Launching in QEMU..."
rm -rf $BUILD_DIR
qemu-system-i386 -cdrom TOS.iso