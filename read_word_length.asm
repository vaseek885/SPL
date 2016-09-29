section .text
        %include "lib.inc"
        global _start 
        _start:
        call read_word

        mov rax, 60
        mov rdi, rdx
        syscall