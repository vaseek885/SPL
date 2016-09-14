section .text

string_length:

    xor rax, rax ; длина строки будет храниться в rax
    
    .iterate:
        mov rdx, [rdi + rax]
        test rdx, rdx ; Если строка закончилась, то выходим.
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
    push dl
    mov rdx, 1 ; количество байт, которое нужно записать
    lea rsi, [rsp - 1] ; адрес строки
    mov rdi, 1 ; пишем в stdout
    mov rax, 1 ; номер системного вызова write
    
    syscall

    ret

print_newline:
    xor rax, rax
    ret


print_uint:
    xor rax, rax
    ret


print_int:
    xor rax, rax
    ret

string_equals:
    xor rax, rax
    ret


read_char:
    xor rax, rax
    ret 

section .data
word_buffer times 256 db 0

section .text

read_word:
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

