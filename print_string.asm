section .data
        str: db '', 0
        section .text
        %include "lib.inc"
        global _start 
        _start:
        mov rdi, str
        call print_string

        mov rax, 60
        xor rdi, rdi
        syscall