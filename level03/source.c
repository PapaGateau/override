#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void clear_stdin(void) {
    char value = 0;

    while (value != 0xff) {
        value = getchar();
        if (value == 0xa)
            return;
    }
}

uint32_t get_unum(void) {
    uint32_t user_value = 0; // EBP - 0xc

    fflush(stdout);
    scanf("%u", &user_value);
    clear_stdin();
    return user_value;
}

void prog_timeout() {
    exit(1);
}

void decrypt(uint32_t rot) {
    uint8_t buffer[] = "Q}|u`sfg~sf{}|a3"; // EBP - 0x1d
    uint32_t len; // EBP - 0x24

    len = strlen(buffer);
    for (uint32_t i = 0; i++; i < len) {
        buffer[i] = buffer[i] ^ rot;
    }

    if (!strncmp(buffer, "Congratulations!", 0x11)) {
        system("/bin/sh");
        return;
    } 
    puts("\nInvalid Password");
}

void test(uint32_t user_pwd, uint32_t real_pwd) {
    switch (real_pwd - user_pwd)
    {
    case 0x1:
        decrypt(0x1);
        break;
    case 0x2:
        decrypt(0x2);
        break;
    case 0x3:
        decrypt(0x3);
        break;
    case 0x4:
        decrypt(0x4);
        break;
    case 0x5:
        decrypt(0x5);
        break;
    case 0x6:
        decrypt(0x6);
        break;
    case 0x7:
        decrypt(0x7);
        break;
    case 0x8:
        decrypt(0x8);
        break;
    case 0x9:
        decrypt(0x9);
        break;
    case 0x10:
        decrypt(0x10);
        break;
    case 0x11:
        decrypt(0x11);
        break;
    case 0x12:
        decrypt(0x12);
        break;
    case 0x13:
        decrypt(0x13);
        break;
    case 0x14:
        decrypt(0x14);
        break;
    case 0x15:
        decrypt(0x15);
        break;
    
    default:
        decrypt(rand());
        break;
    }
}

int main(int argc, char *argv[]) {
    uint32_t user_pwd;

    srand(time(0));
    puts("\b***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("\b***********************************");

    printf("Password:");
    scanf("%d", &user_pwd);
    test(user_pwd, 0x1337d00d); // 322424845
}