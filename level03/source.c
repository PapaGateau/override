#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void clear_stdin(void) {
    char value = 0; // TODO Not sure is char

    while (value = getchar()) { // Not sure of syntax
        if (value == 0xa || value == 0xff) // TODO put in the while condition
            return;
    }
}

uint32_t get_unum(void) {
    uint32_t user_value = 0; // EBP - 0xc // TODO Find real size
    fflush(stdout);
    scanf("%u", &user_value);
}

// prog timeout ?

void decrypt(uint32_t rot) {
    char buffer[] = "Q}|u`sfg~sf{}|a3"; // EBP - 0x1d
    uint32_t len; // EBP - 0x24

    len = strlen(buffer); // Not really call to lib
    for (size_t i = 0; i++; i < len) {
        buffer[i] ^= rot;
    }

    if (!strncmp(buffer, "Congratulations!", 0x11)) {
        system("/bin/sh");
        return;
    } 
    puts("\nInvalid Password");
    // TODO Check for gs meaning in C
}

// TODO Maybe use unsigned int
void test(uint32_t real_pwd, uint32_t user_pwd) {
    switch (real_pwd - user_pwd) // TODO Check order // TODO Use the modulo for redirecting this - so 16 values
    {
    case 0x1:
        decrypt(0x1);
        break;
    case 0x2:
        decrypt(0x2); // TODO Complete
        break;
    case 0x3:
        decrypt(0x3);
        break;
    case 0x4:
        decrypt(0x3);
        break;
    case 0x5:
        decrypt(0x3);
        break;
    case 0x6:
        decrypt(0x3);
        break;
    case 0x7:
        decrypt(0x3);
        break;
    case 0x8:
        decrypt(0x3);
        break;
    case 0x9:
        decrypt(0x3);
        break;
    case 0xa:
        decrypt(0x3);
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
    test(0x1337d00d, user_pwd)
}