section .text

string_length:
    xor rax, rax ; длина строки
    .cycle:
        mov dl, [rdi + rax]
        test dl, dl ; 
        jz .exit
        inc rax
        jmp .cycle
    .exit:
    ret

print_string:
    push rdi
    call string_length
    pop rdi

    mov rdx, rax ; сколько байт записываем
    mov rsi, rdi ; адрес строки
    mov rdi, 1 ; дескриптор stdout
    mov rax, 1 ; системный вызов write
    syscall
    ret

print_char:
    push di ; 
    mov rdx, 1 ; количество байт для записи
    mov rdi, 1 ; дескриптор stdout
    mov rax, 1 ; номер системного вызова write
    mov rsi, rsp ; адрес строки
    syscall
    pop di
    ret

print_newline:
    mov rdi, 0xA
    call print_char
    ret

print_uint:
    mov r10, 10 ; основа десятичной системы счисления
    mov rax, rdi
    mov r8, rsp
    sub rsp, 21 ; 21 - максимально необходимый размер буфера
    ; признак конца строки
    dec r8
    mov byte[r8], 0x00
    
    .cycle: 
        xor rdx, rdx
        div r10 ; rax - делимое
        add rdx, '0'
        dec r8
        mov byte[r8], dl
        test rax, rax
        jnz .cycle

    mov rdi, r8
    call print_string
    
    add rsp, 21 ; 
    ret

print_int:
    test rdi, rdi
    js .minus ; отрицательное число

    .plus:
        call print_uint
    ret
    .minus:
        push rdi

        mov rdi, '-'
        call print_char

        pop rdi

        not rdi
        inc rdi

        call print_uint
    ret

string_equals:
    ; rdi - указатель 1
    ; rsi - указатель 2
    xor rax, rax

    .iterate:
        mov r8b, [rdi]
        mov r9b, [rsi]

        inc rdi
        inc rsi

        cmp r8b, r9b
        je .equals

        .not_equals:
            mov rax, 0
            ret

        .equals:
            test r8b, r9b
            jz .exit

        jmp .iterate
    .exit:
        mov rax, 1
    ret

read_char:
    xor ax, ax ; ВОЛШЕБНАЯ СТРОЧКА
    push ax ; выделяю буф. размером 2 Byte
    
    mov rax, 0 ; номер системного вызова read
    mov rdi, 0 ; дескриптор stdin
    mov rsi, rsp ; буфер
    mov rdx, 1 ; количество байт для чтения
    syscall

    pop ax
    ret

section .data ; по какой-то неводомой причине здесь можно писать .data :D
word_buffer times 256 db 0

section .text

read_word:
    xor rdx, rdx ; длина строки

    .read_next:
        push rdx
        call read_char
        pop rdx

        cmp al, 0x20
        jz .check
        cmp al, 0x09
        jz .check
        cmp al, 0x0A
        jz .check

        test al, al
        jz .finish

        mov byte[word_buffer + rdx], al
        inc rdx

        jmp .read_next

    .check:
        test rdx, rdx
        jz .read_next

    .finish:
        mov byte[word_buffer + rdx], 0x00
        mov rax, word_buffer
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
    mov r10, 10 ; основанеие СС
    xor rax, rax ; прочитанное число
    xor r9, r9 ; длина прочитаного числа
    ; r8b - очередная цифра

    .iterate:
        mov r8b, [rdi + r9]

        cmp r8b, '0'
        jl .exit
        cmp r8b, '9'
        jg .exit

        sub r8b, '0'
        mul r10     ; здесь мы портим rdx
        add rax, r8

        inc r9
        jmp .iterate

    .exit:
        mov rdx, r9
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    mov r8b, [rdi]
    cmp r8b, '-'
    jnz .plus

    .minus:
        inc rdi
        call parse_uint

        not rax
        inc rax

        inc rdx
    ret
    .plus:
        call parse_uint
    ret

string_copy:
    ; rdi - адрес первого символа строки (далее - очередного символа)
    ; rsi - адрсе места вставки
    xor rax, rax

    .iterate:
        mov al, [rdi]

        ; check
        test al, al
        jz .exit

        mov byte[rsi], al

        inc rdi
        inc rsi

        jmp .iterate

    .exit:
        mov byte[rsi], 0
    ret
