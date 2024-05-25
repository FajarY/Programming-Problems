section .bss
    buffer resb 1000

section .text
    global _start

_start:
    mov rdi, buffer
    mov rsi, 12
    call _get_string

    mov rdi, buffer
    call _asm_print_string

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
    add rsp, 1
    mov [rsi], dl
    mov rdx, 1

    syscall

    sub rsp, 1

    pop rsi
    pop rdi
    pop rax
    pop rdx
    
    skip_put_char:
    ret

_asm_print_string:
    push rdi
    push rsi

    loop_string:
    cmp byte [rdi], 0
    je end_loop

    mov rsi, rdi
    mov rdi, [rsi]

    call _put_char
    shr rdi, 8
    call _put_char
    shr rdi, 8
    call _put_char
    shr rdi, 8
    call _put_char
    shr rdi, 8
    call _put_char
    shr rdi, 8
    call _put_char
    shr rdi, 8
    call _put_char
    shr rdi, 8
    call _put_char

    mov rdi, rsi
    add rdi, 1

    jmp loop_string

    end_loop:

    pop rsi
    pop rdi
    ret

_clear_buffer:
    push rsi
    push rbp

    mov rbp, rsi
    add rsi, rdi

    loop_buffer:

    cmp rbp, rsi
    jge end_loop_buffer

    mov byte [rbp], 0
    add rbp, 1

    jmp loop_buffer

    end_loop_buffer:

    pop rbp
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