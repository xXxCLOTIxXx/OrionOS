ENTRY(start)

SECTIONS {
    . = 0x100000;

    .text : {
        *(.multiboot_header)
        *(.text)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}
