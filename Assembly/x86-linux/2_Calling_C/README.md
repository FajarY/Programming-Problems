### What i've learned

- Flush
    - When i call the c function using printf, it doesnt put it directly to stdout, so i need to call fflush some time

- Function Parameters
    - When i want to call a c function that takes some parameters the orders are :
    - rdi, rsi, rdx, rcx, r8, r9 (For Integers)
    - Beyond that we need to push it to stack pointer

- Put Char
    - The system call that prints a string doesn't print the characters directly, instead it takes a pointer to the string, hence we need to put the character into the stack pointer first to make passing pointer doable

- C Function Calling
    - To call the C function simply use `extern [function_name]`

- Compiling
    - Also gcc makes some headers and it will intefere with the assembly _start, so we need to add the flag -nostartfiles
    - Also add -lc to make sure that the linked added the standard c library to the executable
    - no-pie is to disable PIE generation for various reasons, such as compatibility with certain tools or environments.