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
    uint32_t diff = real_pwd - user_pwd;

    switch (diff)
    {
    case 0x1: // 1
    case 0x2:
    case 0x3:
    case 0x4:
    case 0x5:
    case 0x6:
    case 0x7:
    case 0x8:
    case 0x9: // 9
    case 0x10: // 16
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15: // 21
        decrypt(diff);
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