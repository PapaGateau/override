#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    char buffer[0x20]; // 32; ESP + 0x20
    pid_t waitedPid = 0; // ESP + 0x1c
    pid_t backupPid; // ESP + 0xa0
    pid_t thirdPid; // ESP + 0xa4
    int var2 = 0; // ESP + 0xa8

    pid_t ret = fork(); // ESP + 0xac

    memset(buffer, 0, 0x20);
    
    if (ret == 0) {
        prctl(1, 1);
        ptrace(0, 0, 0, 0);
        puts("Give me some shellcode, k");
        gets(buffer);
        return 0;
    }

    wait(&waitedPid);
    backupPid = waitedPid;

    if (backupPid & 0x7f == 0) {
        puts("child is exiting");
    }
    thirdPid = backupPid;
    if (((int8_t)(thirdPid & 0x7f + 1) / 2) > 0) {
        puts("child is exiting");
    }

    if (ptrace(3, ret, 0x2c, 0) == 0xb) {
        puts("no exec() for you");
        kill(ret, 9);
    }

    return 0;
}
