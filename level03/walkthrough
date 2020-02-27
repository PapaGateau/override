# Level03
Running this program will show a simple password prompt
```bash
./level03
***********************************
*		level03		**
***********************************
Password:test

Invalid Password
```

## Disassembly
We can see that this program does a call to `bin/sh` but it is after a `strcmp`.			
Two strings "Q}|u`sfg~sf{}|a3" and "Congratulations!" are used for the comparison.		
Using an ascii table and checking repeated characters, we notice that the first string is a `rot-18` of the second string.		

The first string passes through the `decrypt()` function before the comparison. This function seems to xor the the characters of the string in a loop and repeats the process based on a value received in parameters.

Our input string for the password prompt is received through `scanf(%u)`. If the difference between our input value and `322424845` is greater than `0x15` (21) the decrypt function will use a `rand()` generated number for its operations, otherwise it will use the resulting difference.		

The `decrypt()` function performs the equivalent of a rot+1 with each loop, so if we input the correct value, we should be able to match the two strings and reach the `/bin/sh` call!

To reverse the first string we want the `decrypt` loop to occur 18 times, fortunately 18 is inferior to 21 so if we enter `322424845-18=322424827` we should pass the conditional jump.

```bash
./level03
***********************************
*		level03		**
***********************************
Password:322424827
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```


















this program compares two strings, if the comparison is true it will call /bin/sh
The first string goes throguh a decryption function that will xor each of its characters X number of times, where X is 322424845 - our input number
however, unless the result of the substraction is between 1 and 21, it will use a rand generated number instead
After inspecting the encrypted string we can see that it is a rot 18 of the second string
this means we will simply have to enter a number that will result as 18 after substracting it to 322424845

Password: 322424827
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf

