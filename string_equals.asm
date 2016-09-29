section .data
             str1: db 'asd',0
             str2: db 'asd',0
        section .text
        %include "lib.inc"
        global _start
        _start:
        mov rdi, str1
        mov rsi, str2
        call string_equals
        mov rdi, rax
        mov rax, 60
        syscall