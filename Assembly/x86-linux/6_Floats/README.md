### What i've learnt

- xmm Register
    - xmm registers are used to store floating points. with the size of the register are 128 bit. If we want to call a c function and pass a float parameter, we have to put it to the xmm registers in order, ex : xmm0, xmm1, ...

- Floating Points
    - Floating point numbers can be quite dificult since there is no standardized way to initialize a float on runtime. We have to initialize the floating point variable in the data section first to make it human readable.
    - But on the other way to initialize a floating value in runtime is to initialize it with the hexadecimal literal.
    - `movss` is used to to move a scalar single percision floating point values. it is generaly safer to use movss to move a floting point.
    - `movd` is used to move value and treated as a raw 32 bit values. We have to use this instruction to move between and xmm register, general purpose regiters, and also memory.