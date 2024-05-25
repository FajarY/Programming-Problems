section .bss
    buffer resb 1000

section .text
    global _start

_start:
    mov rdi, buffer
    mov rsi, 12
    call _get_string

    call print_string

    call print_endl
    call _exit_success

_get_string:
    push rdi
    push rsi

    loop_get_string:

    cmp rsi, 0
    jle end_loop_get_string

    call _get_char
    add rdi, 1
    sub rsi, 1

    jmp loop_get_string

    end_loop_get_string:
    
    pop rsi
    pop rdi

    ret

_get_char:
    push rax
    push rdi
    push rsi
    push rdx

    mov rsi, rdi
    mov rax, 0
    mov rdi, 0
    mov rdx, 1
    syscall

    pop rdx
    pop rsi
    pop rdi
    pop rax

    ret

_put_char:
    cmp rdi, 0
    je skip_put_char

    push rdx
    mov rdx, rdi
    push rax
    push rdi
    push rsi

    mov rax, 1
    mov rdi, 1

    mov rsi, rsp
    add rsp, 4
    mov dword [rsi], 0

    mov [rsi], dl
    mov rdx, 1

    syscall

    sub rsp, 4

    pop rsi
    pop rdi
    pop rax
    pop rdx
    
    skip_put_char:
    ret

_asm_print_string:
    push rdi
    push rsi

    mov rsi, rdi
    mov rdi, [rdi]

    cmp byte dil, 0
    je go_pop
    call _put_char

    mov rdi, rsi
    add rdi, 1
    call _asm_print_string

    go_pop:

    pop rdi
    pop rsi
    ret

_exit_success:
    mov rax, 60
    mov rdi, 0
    syscall

extern print_number
extern print_string
extern print_endl
extern flush