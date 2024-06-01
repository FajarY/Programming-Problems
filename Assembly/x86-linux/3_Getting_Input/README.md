### What i've learned

- Loop
    - You can build a loop by using compare and jump instruction. for compare you use `cmp register, data`. And after that if you want to jump you can use `je` for jump equals, `jg` jump greater, `jl` jump lower, `jge` jump greater equal, etc.
    - You can also just use `jmp` to directly jump into a label
    - A label is kinda like a subroutine
    - It is pretty hard to make sure the loop is right and not make it to segfault

- Section .bss
    - This section is for variables that you can change
    - `resb` is for reserve byte

- Also Some Failures
    - Implementing printing in assembly is a failure at this point. So many segfaults. Maybe next time