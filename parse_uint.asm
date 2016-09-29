section .data
        input: db '1', 0
        section .text
        %include "lib.inc"
        global _start 
        _start:
        mov rdi, input
        call parse_uint
        push rdx
        mov rdi, rax
        call print_uint
        mov rax, 60
        pop rdi
        syscall