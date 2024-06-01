section .data
    header db "****SUBROUTINE PROGRAM****", 10
    header_len equ $-header
    first_string db "This is a second string", 10
    first_string_len equ $-first_string;
    endl db "", 10

section .text
    global _start

_start:
    mov rax, header
    mov rdi, header_len

    push rax
    push rdi
    call _print
    add rsp, 16

    mov rax, first_string
    mov rdi, first_string_len
    push rax
    push rdi
    call _print
    add rsp, 16

    mov rax, endl
    mov rdi, 1
    push rax
    push rdi
    call _print
    add rsp, 16

    call _exit_success

_print:
    mov rbp, rsp
    push rax
    push rdi
    push rsi
    push rdx

    mov rax, 1
    mov rdi, 1
    mov rsi, [rbp + 16]
    mov rdx, [rbp + 8]
    syscall

    pop rdx
    pop rsi
    pop rdi
    pop rax

    ret

_exit_success:
    mov rax, 60
    mov rdi, 0
    syscall
    ret