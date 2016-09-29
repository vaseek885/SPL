section .text
        %include "lib.inc"
        global _start 
        _start:
        mov rdi, 123123
        call print_uint
        mov rax, 60
        xor rdi, rdi
        syscall