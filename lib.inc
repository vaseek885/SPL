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
    xor rax, rax
    xor r8, r8
    xor r9, r9

    
    ;Для нашей строки понадобится 21 байт места максимум

    mov r8, 10 ; делим на 10
    mov r9, rsp
    sub rsp, 22
    mov rax, rdi
    test rax, rax 
    dec r9 
    mov qword[r9], 0

    .iterate:
        xor rdx, rdx
        dec r9
        div r8
        add rdx, '0'
        mov byte[r9], dl
        test rax, rax
        jz .next
        jmp .iterate
    .next:
    mov rdi, r9
    call print_string
    add rsp, 22
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
    xor rax, rax
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

