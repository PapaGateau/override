#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

int main()
{
    char buffer[0x20]; // 32 ; ESP + 0x20
    pid_t waitedPid = 0; // ESP + 0x1c
    pid_t backupPid; // ESP + 0xa0
    pid_t thirdPid; // ESP + 0xa4
    int var2 = 0; // ESP + 0xa8

    pid_t pid = fork(); // ESP + 0xac

    memset(buffer, 0, 0x20);
    
    if (pid == 0) {
        prctl(1, 1);
        ptrace(0, 0, 0, 0);
        puts("Give me some shellcode, k");
        gets(buffer);
        return 0;
    }

    while (1) {
        wait(&waitedPid);
        backupPid = waitedPid;
        thirdPid = backupPid;
        if (WIFEXITED(thirdPid)) {
            puts("child is exiting");
            return 0;
        }

        if (ptrace(3, ret, 0x2c, 0) == 0xb) { // If syscall exec
            puts("no exec() for you");
            kill(ret, 9);
        }
    }

    return 0;
}
