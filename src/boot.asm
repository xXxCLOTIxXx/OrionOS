BITS 32
extern cmain

%define MULTIBOOT_HEADER_MAGIC                  0x1BADB002

; This should be in %eax. 
%define MULTIBOOT_BOOTLOADER_MAGIC              0x2BADB002

; Alignment of multiboot modules. 
%define MULTIBOOT_MOD_ALIGN                     0x00001000

; Alignment of the multiboot info structure. 
%define MULTIBOOT_INFO_ALIGN                    0x00000004

; Flags set in the ’flags’ member of the multiboot header. 

; Align all boot modules on i386 page (4KB) boundaries. 
%define MULTIBOOT_PAGE_ALIGN                    0x00000001

; Must pass memory information to OS. 
%define MULTIBOOT_MEMORY_INFO                   0x00000002

; Must pass video information to OS. 
%define MULTIBOOT_VIDEO_MODE                    0x00000004

%define FLAGS (MULTIBOOT_PAGE_ALIGN | MULTIBOOT_VIDEO_MODE | MULTIBOOT_MEMORY_INFO)
%define CHECKSUM -(MULTIBOOT_HEADER_MAGIC + FLAGS)

%define STACKSIZE 1024 * 16


section .multiboot_header



  ;Multiboot definition
  align 4
  ;Required
  dd MULTIBOOT_HEADER_MAGIC
  dd FLAGS
  dd CHECKSUM

  dd 0, 0, 0, 0, 0

  ;Graphics
  dd 0    ;Mode, 0 - linear, 1 - text mode
  ;dd 1920, 1080, 32  ;Width, Height, BPP
  dd 640, 480, 32  ;Width, Height, BPP

section .text
global start
start:
    cli

    mov esp, stack_top

    push eax 
    push ebx 
    call cmain 
    add esp, 4

    cli
halt:
    hlt
    jmp halt

    ;Stack
    section .bss
    align 16
    stack_bottom:
        resb STACKSIZE                  
    stack_top:



