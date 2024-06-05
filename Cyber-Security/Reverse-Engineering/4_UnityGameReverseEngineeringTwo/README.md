### What i've learned

- Powerfull Dumping using magisk and zygisk method
    - Turns out there is another method of dumping that depends on magisk and zygisk module. The zygisk module is essentially an injector that runs on the android zygote process (The one that is responsible to spawn new process). We can uitilize the il2cpp zygisk dumper to bypass il2cpp protection on the static apk. Its also bypasses some obfuscation.
    - Here is a screenshot of what i did:
    - ![Unlimited money](./0.png)
    - I also tricked the game into thinking that i've bought some packs
    - ![Purchasing](./2.jpg)
    - And also this is my attempt to get the dump file of a protected game
    - ![Protection Dumping](./1.png)