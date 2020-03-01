#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void clear_stdin() {
    int8_t val = 0;

    while (1) {
        val = getchar();
        if (val == '\n' || val == EOF) {
            return;
        }
    }
}

unsigned int get_unum(void) {
    uint32_t var1 = 0;

    fflush(stdout);
    scanf("%u", &var1);
    clear_stdin();
    return var1;
}

void prog_timeout() {
    exit(1);
}

int store_number(int32_t *buffer) {
    uint32_t number; // EBP - 0x10
    uint32_t index; // EBP - 0xc

    printf(" Number: ");
    number = get_unum();
    printf(" Index: ");
    index = get_unum();

    if (!(index % 3) || number >> 0x18 != 0xb7) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }
    buffer[index] = number;
    return 0;
}

int read_number(int32_t *buffer) {
    uint32_t index = 0; // EBP - 0xc

    printf(" Index:");
    index = get_unum();
    printf(" Number at data[%u] is %u\n", index, buffer[index]);
    return 0;
}

int main(int argc, char *argv[], char *envp[]) {
    int8_t buffer[0x64] = {0}; // ESP + 0x24
    int8_t **av = argv; // ESP + 0x1c
    int8_t **ep = envp; // ESP + 0x18

    int32_t cmd_ret = 0; // ESP + 0x1b4
    int8_t cmd_buffer[20] = {0}; // ESP + 0x1b8

    while (*av) {
        memset(*av, 0, strlen(*av));
        *av++;
    }
    while (*ep) {
        memset(*ep, 0, strlen(*ep));
        *ep++;
    }

    puts("----------------------------------------------------\n  Welcome to wil's crappy number storage service!   \n----------------------------------------------------\n Commands:                                          \n    store - store a number into the data storage    \n    read  - read a number from the data storage     \n    quit  - exit the program                        \n----------------------------------------------------\n   wil has reserved some storage :>                 \n----------------------------------");
    
    while (1) {
        printf("Input command: ");
        fgets(cmd_buffer, 0x14, stdin);
        cmd_buffer[strlen(&cmd_buffer) - 1] = 0;

        if (!strncmp(cmd_buffer, "store", 5)) {
            cmd_ret = store_number(buffer);
        } else if (!strncmp(cmd_buffer, "read", 4)) {
            cmd_ret = read_number(buffer);
        } else if (!strncmp(cmd_buffer, "quit", 4)) {
            return 0;
        }

        if (cmd_ret == 0) {
            printf(" Completed %s command successfully\n", &cmd_buffer);
        } else {
            printf(" Failed to do %s command\n", &cmd_buffer);
        }
        memset(&cmd_buffer, 0, 0x14);
    }
    return 0;
}