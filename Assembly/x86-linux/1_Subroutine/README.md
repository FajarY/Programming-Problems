### What i've learned

- Equ
    - with $ means the current location counter. if we want to take the length we simply just subtract $ with the pointer to the start of a variable. like `$ - hello`

- Subroutine
    - Like a function, that can be called using `call [subroutine]`

- Registers
    - rsp, 64 Bit Stack Pointer. Points to the top of stack
    - rbp, 64 Bit Base Pointer, a general purpose register that we can put stack pointer to
    - rsi, 64 Bit Register Source Index, a register that is typically used for holding a memory address, or a general purpose register to hold memory references
    - rdi, 64 Bit Destination Index, commonly used to hold the memory address destination.
    - rdx, 64 Bit Data Register, a general purpose register that is commonly stored for length, index, etc