section .text
        %include "lib.inc"
        global _start 
        _start:
        call read_word
        mov rdi, rax
        call print_string

        mov rax, 60
        xor rdi, rdi
        syscall