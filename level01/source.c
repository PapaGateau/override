#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a_user_name[0x100];

int verify_user_name() {
    puts("verifying username....\n");
    return strncmp("dat_wil", a_user_name, 7) ? 1 : 0; // Same comportment as strncmp but using local optimisation
}

int verify_user_pass(char *password) {
    return strncmp("admin", password, 5) ? 1 : 0; // Same comportment as strncmp but using local optimisation
}

int main(int argc, char *argv[]) {
    // Not sure of size, probably not this since overflow
    char buffer[0x40]; // =64 // ESP + 0x1c
    int ret = 0; // 0x5c

    memset(buffer, 0, 0x10); // Not really memset but this uses the operations optimisation
    puts("********* ADMIN LOGIN PROMPT *********");

    printf("Enter Username: ");
    fgets(a_user_name, 0x100, stdin); // 256
    ret = verify_user_name();
    if (ret) {
        puts("nope, incorrect username...\n");
        return 1;
    }

    puts("Enter Password: ");
    fgets(buffer, 0x64, stdin); // =100
    ret = verify_user_pass(buffer);
    if (ret) {
        puts("nope, incorrect password...\n");
        return 1;
    }
    
    return 0;
}