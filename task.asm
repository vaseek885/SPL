section .data
        str: db 'file', 0  
        section .text
        %include "lib.inc"
        global _start
        _start:
        call read_word
        mov rdi, rax
        call parse_int
        mov rdi, rax
        ; rax - int 
        mov rdi, 1
.loop:
        xor rdx, rdx
        inc rdi
        push rax
        xor rax, rdi
        jz .good
        div rdi
        pop rax
        test rdx, rdx
        jnz .loop
        jmp .bad

.good:  pop rax
        mov rax, 1
        jmp .end

.bad:   mov rax, 0

.end:
        ;push rax
        ;mov rax, 2
        ;mov rdi, str
        ;mov rsi, 02
        ;mov rdx, 0777
        ;syscall
        ;mov rdx, rax
        ;pop rax
        
        mov rdi, rax
        call print_int
        mov rdi, 0
        mov rax, 60
        syscall
