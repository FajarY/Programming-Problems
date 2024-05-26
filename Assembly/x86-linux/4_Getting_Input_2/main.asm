section .data
    header db "****ASSEMBLY****", 10
    padding db "", 0 ;If not then header and get_input_header become one???
    get_input_header db "input: ", 0
    out_input_header db "output: ", 0

section .text
    global _start

_start:
    mov rdi, header
    call print_string
    mov rdi, get_input_header
    call print_string

    sub rsp, 1024 ;Allocate 1024 byte buffer, allocate with the multiply of 16 byte so we dont have to padding
    mov rdi, rsp

    call _get_input

    mov rdi, out_input_header
    call print_string

    mov rdi, rsp
    call print_string

    add rsp, 1024

    call print_endl

    call _exit_success

_get_input:
    push rdi ;Caller saved, rdi is volatile, also for systemv 16 byte allignment before calling a function, we put 8 bytes to the stack, since when we call subroutine 8 bytes is already putted for the return address
    call get_string
    pop rdi
    ret

_exit_success:
    mov rax, 60
    mov rdi, 0
    syscall

extern print_number
extern get_string
extern print_string
extern print_endl