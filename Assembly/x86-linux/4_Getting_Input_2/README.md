### What i've learned

- 16 Byte Alligment For Calling Function
    - I need to make sure that the stack pointer is in the multiply of 16 byte. If not segfault will occour, https://stackoverflow.com/questions/49391001/why-does-the-x86-64-amd64-system-v-abi-mandate-a-16-byte-stack-alignment

- Stack Pointer
    - Since the stack is allocated in a decreasing manner, if we want to allocate some stack memory we can use `sub rsp, 8` this means allocate 8 bytes to the stack, and to pop it we can `add rsp, 8`

- Caller Saved & Calle Saved Registers
    - There is a concept called caller and callee saved register, if i want to call a c function i need to make sure to save the caller registers, since the function in c doesn't have the obligation to save it.
    - Caller saved register are registers that we don't have the obligation to save, but to maintain integrety we have to save it ourself before calling outsider function. The registers are `rax`, `rdi`, `rsi`, `rdx`, `r8`, `r9`, etc
    - Callee saved registers are registers that we must maintain the integrety, so that our program can run safely. The registers are `rsp`, `rbx`, `rbp`, `r12`, `r13`, etc
    - Source : https://web.stanford.edu/class/archive/cs/cs107/cs107.1174/guide_x86-64.html