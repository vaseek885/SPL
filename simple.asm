section .data ; 
word_buffer times 256 db 0

section .text

read_word:
    xor rdx, rdx ; длина строки

    .next:
        push rdx
        call read_char
        pop rdx

        cmp al, 0x20
        jz .skip
        cmp al, 0x09
        jz .skip
        cmp al, 0x0A
        jz .skip

        test al, al
        jz .exit

        mov byte[word_buffer + rdx], al
        inc rdx

        jmp .next

    .skip:
        test rdx, rdx
        jz .next

    .exit:
        mov byte[word_buffer + rdx], 0x00
        mov rax, word_buffer
    ret

read_char:
    xor ax, ax ; 
    push ax ; буфер 2 байта
    
    mov rax, 0 ; read
    mov rdi, 0 ;  stdin
    mov rsi, rsp ; буфер
    mov rdx, 1 ; количество байт 
    syscall

    pop ax
    ret

parse_uint:
    mov r10, 10 ; основа десятичной системы счисления
    xor rax, rax ;  число
    xor r9, r9 ; длина числа
    .cycle:
        mov r8b, [rdi + r9]

        cmp r8b, '0'
        jl .exit
        cmp r8b, '9'
        jg .exit
        mul r10   
        sub r8b, '0'
        add rax, r8
        inc r9
        jmp .cycle

    .exit:
        mov rdx, r9
    ret

global _start
_start: 

