ENTRY(kernel_main)

SECTIONS {
    . = 0x100000; /* Указываем GRUB'у, где загружать ядро в память */
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}
