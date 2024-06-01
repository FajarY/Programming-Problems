section .data
    first_str db "Calling the c printer", 0
    first_str_len equ $-first_str

section .text
    global _start

_start:
    mov rdi, first_str
    call print_something
    call print_endl

    mov rdi, 5
    mov rsi, 10
    call add_number

    mov rdi, rax
    call print_number
    call flush

    mov rdi, 'A'
    call _put_char

    call print_endl

    call flush
    call _exit_success

_put_char:
    push rax
    push rdi
    push rsi
    push rdx
    mov rsi, rdi

    mov rax, 1
    mov rdi, 1
    mov rdx, 1

    mov rbp, rsp
    sub rsp, 1
    mov [rbp], sil
    mov rsi, rbp

    syscall

    add rsp, 1
    pop rdx
    pop rsi
    pop rdi
    pop rax
    ret

_exit_success:
    mov rax, 60
    mov rdi, 0
    syscall

extern flush
extern print_something
extern add_number
extern print_number
extern print_endl