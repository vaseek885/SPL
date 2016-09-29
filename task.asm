section .data
        str: db 'file', 0 
        section .text
        %include "lib.inc"
        global _start
        _start:
        mov rax, 2
        mov rdi, str
        mov rsi, 02
        mov rdx, 0777
        syscall

        xor r13, r13
        push r13
        mov rdi, rax
        mov rax, 0
        mov rsi, rsp
        mov rdx, 3 
        syscall
        pop r13
        
        call string_length
        mov rdi, rax
        mov rax, 60
        syscall