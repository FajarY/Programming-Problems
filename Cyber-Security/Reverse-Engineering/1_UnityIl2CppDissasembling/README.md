### What I've learned

- IL2Cpp Dumper
    - Used to extract classes names, functions names, variables names, and their adresses in the libil2cpp.so binary. But it can't extract the codes of the classes or functions. Pretty usefull if you want to edit the function, because you can offset to a function virtual address

- DnSpy
    - Used for analyzing c# assembly. Used for getting the function virtual address offset.

- Binary Ninja
    - Used for dissasembling of the libil2cpp.so. But the il2cpp dumper offset only works for the 32 bit binary (ARMv7). We can edit the binary of the libil2cpp but requires a knowledge of how everything works in unity and also how ARM assembly works.

- ApkTool
    - Generally used for decompiling and compiling and android apk.

- Screenshots
    - Due to respect for the game developers, i will blur the app that i've currently reverse engineering 
    - ![Reverse Engineering](./0.png)