section .text
        %include "lib.inc"
        global _start 
        _start:
        call read_char
        mov rdi, rax
        mov rax, 60
        syscall