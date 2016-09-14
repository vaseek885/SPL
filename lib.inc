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
    
    call string_length

    mov rdx, rax ; количество байт, которое нужно записать 
    mov rsi, rdi ; адрес строки
    mov rdi, 1   ; пишем в stdout
    mov rax, 1   ; номер системного вызова write
    syscall
    ret

