 section .text
        %include "lib.inc"
        global _start 
        _start:
        mov rdi, 'c'
        call print_char
        mov rax, 60
        xor rdi, rdi
        syscall