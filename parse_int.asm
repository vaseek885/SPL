section .data
        input: db '1', 0
        section .text
        %include "lib.inc"
        global _start 
        _start:
        mov rdi, input
        call parse_int
        push rdx
        mov rdi, rax
        call print_int
        pop rdi
        mov rax, 60
        syscall