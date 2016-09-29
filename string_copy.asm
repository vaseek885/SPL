section .data
        arg1: db '', 0
        arg2: times 1 db  66
        section .text
        %include "lib.inc"
        global _start 
        _start:
        mov rdi, arg1
        mov rsi, arg2
        call string_copy
        mov rdi, arg2 
        call print_string
        mov rax, 60
        xor rdi, rdi
        syscall