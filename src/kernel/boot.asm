bits 32
section .text
    ; Multiboot specification header
    align 4
    dd 0x1BADB002             ; magic
    dd 0x00                   ; flags
    dd - (0x1BADB002 + 0x00)  ; checksum, m + f + c should be zero

    global start
    extern kernel_main  ; это определено в вашем ядре на C++

start:
    cli                 ; блокировка прерываний
    mov esp, stack_space ; установка указателя стека
    call kernel_main     ; вызов функции kernel_main из вашего ядра
    hlt                 ; остановить процессор

section .bss
    resb 8192           ; 8 КБ для стека
stack_space:
