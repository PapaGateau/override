#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]) {
    int var6 = 0; // ESP + 0x24
    char **av = argv; // ESP + 0x1c
    char **ep = envp; // ESP + 0x18
    int var42 = 0;// ESP + 0x14
    char *storage = 0; // Fix this ????? // ESP + 0x1cc

    int cmd_ret = 0; // ESP + 0x1b4
    char *var1 = 0; // ESP + 0x1b8 // TODO Probably a char [0x14] set to 0
    int var2 = 0; // ESP + 0x1bc
    int var3 = 0; // ESP + 0x1c0
    int var4 = 0; // ESP + 0x1c4
    int var5 = 0; // ESP + 0x1c8

    char str[0x64]; // TODO Fix this maybe not 0x64
    memset(str, 0, 0x64); // = 100

    while (*av) {
        var42 = -1;
        memset(*av, 0, strnlen(*av, var42)); // Not really strlen but optimized version
        *av++;
    }
    while (*ep) {
        var42 = -1;
        memset(*ep, 0, strnlen(*ep, var42)); // Not really strlen but optimized version
        *ep++;
    }
    puts("----------------------------------------------------\n  Welcome to wil's crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------");
    
    while (1) {
        printf("Input command: ");
        fgets(&var1, 0x14, stdin);
        var1[strnlen(&var1, var42)] = 0;

        if (!strncmp(var1, "store", 5)) {
            cmd_ret = store_number(&var6);
        } else if (!strncmp(var1, "read", 4)) {
            cmd_ret = read_number(&var6);
        } else if (!strncmp(var1, "quit", 4)) {
            // Do something with storage
            // stack fail check
            return 0;
        }
        if (cmd_ret == 0) {
            printf(" Completed %s command successfully\n", &var1);
            memset(&var1, 0, 0x14);
        } else {
            printf(" Failed to do %s command\n", &var1);
        }
    }
        
}