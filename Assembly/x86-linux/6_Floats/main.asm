section .data
    float_data dd 1.1

section .text
    global _start

_start:
    movss xmm0, dword [float_data]
    call print_float
    call print_endl

    mov eax, 0x40866666 ;Hexadecimal respresentation of 4.3
    movd xmm0, eax
    call print_float
    call print_endl

    call _exit_success

_exit_success:
    mov rax, 60
    mov rdi, 0
    syscall

extern print_float
extern print_endl