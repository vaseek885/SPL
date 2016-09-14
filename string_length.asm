section .data
        str: db 'asdkbasdka', 0
        section .text
        %include "lib.inc"
        global _start
        _start:
        mov rdi, str
        call string_length
        mov rdi, rax
        mov rax, 60
        syscall