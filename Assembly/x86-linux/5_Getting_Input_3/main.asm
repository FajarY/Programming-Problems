section .data
    header db "*************ASSEMBLY PROGRAM****************", 10
    header_pad db "", 0
    input_info db "Input a string, for ending use \n : ", 0
    input_info_pad db "" 0
    output_info db "Output from inputting : ", 0
    output_info_pad db "" 0

section .text
    global _start

_start:
    mov rdi, header
    call _print_string_from_buffer

    mov rdi, input_info
    call _print_string_from_buffer

    sub rsp, 1024

    mov rdi, rsp
    mov rsi, 1024
    call _clear_buffer

    mov rdi, rsp
    call _get_string_to_buffer

    mov rdi, output_info
    call _print_string_from_buffer

    mov rdi, rsp
    call _print_string_from_buffer

    mov rdi, 10
    call _put_char

    add rsp, 1024
    call _exit_success

_clear_buffer:
    loop_clear_buffer:

    cmp rsi, 0
    jle end_clear_buffer
    mov byte [rdi], 0
    add rdi, 1
    sub rsi, 1

    jmp loop_clear_buffer

    end_clear_buffer:
    ret

_get_char_to_buffer:
    mov rsi, rdi
    mov rax, 0
    mov rdi, 0
    mov rdx, 1
    syscall

    ret

_put_char:
    sub rsp, 1
    mov byte [rsp], dil
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov rdx, 1
    syscall
    add rsp, 1
    ret

_print_string_from_buffer:
    loop_print_string_from_buffer:

    push rdi
    mov rsi, rdi
    mov rdi, 0
    mov byte dil, [rsi]

    cmp byte dil, 0
    je end_print_string_from_buffer

    call _put_char

    pop rdi
    add rdi, 1
    jmp loop_print_string_from_buffer

    end_print_string_from_buffer:
    add rsp, 8

    ret

_get_string_to_buffer:
    loop_get_string_to_buffer:

    push rdi
    call _get_char_to_buffer
    pop rdi

    cmp byte [rdi], 10
    je end_get_string_to_buffer

    add rdi, 1
    jmp loop_get_string_to_buffer

    end_get_string_to_buffer:
    mov byte [rdi], 0
    ret

_exit_success:
    mov rax, 60
    mov rdi, 0
    syscall