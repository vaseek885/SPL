section .text

string_length:

    xor rax, rax ; длина строки будет храниться в rax
    
    .iterate:
        mov rdx, [rdi + rax]
        test dl, dl ; Если строка закончилась, то выходим.
        jz .exit

        inc rax
        jmp .iterate
    
    .exit:
    ret
print_string:
    push rdi
    call string_length
    pop  rdi

    mov rdx, rax ; количество байт, которое нужно записать 
    mov rsi, rdi ; адрес строки
    mov rdi, 1   ; пишем в stdout
    mov rax, 1   ; номер системного вызова write
    syscall
    ret

print_char:
    xor rax, rax
    push di
    mov rdx, 1 ; количество байт, которое нужно записать
    mov rsi, rsp ; адрес символа
    mov rdi, 1 ; пишем в stdout
    mov rax, 1 ; номер системного вызова write
    syscall
    pop di
    ret

print_newline:
    mov rdi, 10
    call print_char
    ret


print_uint:
    ; rdi - 8-ми байтное беззнаковое число
    mov rax, rdi

    mov r10, 10 ; основание СС

    mov r9, rsp
    sub rsp, 21 ; выделяем буфер

    ; записываем признак конца строки
    dec r9
    mov byte[r9], 0x00
    
    .iteratey: ; цикл с пост-условием
        xor rdx, rdx

        div r10 ; rax - делимое

        ; число -> символ ASCII
        add rdx, '0'

        ; кладем очередную цифру в стек
        dec r9
        mov byte[r9], dl
        
        ; ценая часть = 0 ?
        test rax, rax
        jnz .iteratey

    mov rdi, r9
    call print_string
    
    add rsp, 21 ; восстанавливаем stack
    ret


print_int:
    xor rax, rax
    test rdi, rdi
    js .negative

    call print_uint
    ret

    .negative:
    push rdi
    mov rdi, '-'
    call print_char
    pop rdi
    not rdi
    inc rdi
    call print_uint
    ret

string_equals:
    xor rax, rax
    ret


read_char:
    xor ax, ax
    push ax ; 
    
    mov rax, 0 ; 
    mov rdi, 0 ; 
    mov rsi, rsp ; 
    mov rdx, 1 ; 
    syscall

    pop ax
    ret


section .data
word_buffer times 256 db 0

section .text

read_word:
    xor rdx, rdx ; длина строки
.next:
    push rdx
    call read_char
    pop rdx
    cmp al, 0x09
    jz .done
    cmp al, 0x20
    jz .done
    cmp al, 0x0A
    jz .done

    test al, al
    jz .exit

    mov byte[word_buffer + rdx], al
    inc rdx

    jmp .next

.done:
    test rdx, rdx
    jz .next

.exit:
    mov byte[word_buffer + rdx], 0x00
    mov rax, word_buffer

    ret

; rdi points to a string
; returns rax: number, rdx : length

parse_uint:
    mov r10, 10 ; основанеие СС
    xor rax, rax ; прочитанное число
    xor r8, r8
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
    xor rax, rax
    ret 


string_copy:
    xor rax, rax
    .iterate:
    mov al, [rdi]
    mov byte[rsi], al

    test al,al
    jz .exit

    inc rdi
    inc rsi
    jmp .iterate

    .exit:
    ret

