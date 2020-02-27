# Level00

This binary contains a call to `bin/sh` but we need to pass a conditional jump to run it:

```asm
cmp eax, 0x149	; eax contains the result of scanf(%d) our input. 0x149 is 5276 in decimal
jne 0x0804850d	; jumps after the system("bin/sh") call
```

All we have to do is input 5276 when running the program

```bash
./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```
