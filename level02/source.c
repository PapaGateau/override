#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char*argv[]) {
    // TODO Maybe backup of av, ac

    int8_t username_buffer[0x29]; // RBP - 0x70 // TODO Find real size
    int8_t pass_buffer[0x42]; // RBP - 0xa0 // TODO Find real size
    int8_t pwd_buffer[0x42]; // RBP - 0x110 // TODO Find real size
    size_t read_ret = 0; // EBP - 0xc
    FILE *pwd_file = 0;// RBP - 0x8

    memset(username_buffer, 0, 12); // It's not a call to the lib, but it's same comportement
    memset(pass_buffer, 0, 5); // It's not a call to the lib, but it's same comportement
    memset(pwd_buffer, 0, 12); // It's not a call to the lib, but it's same comportement

    pwd_file = fopen("/home/users/level03/.pass", 'r');
    if (pwd_file == 0) {
        fwrite("ERROR: failed to open password file\n", 1, 0x24, stderr);
        exit(1);
    }

    read_ret = fread(pass_buffer, 1, 0x29, pwd_file);
    pass_buffer[strcspn(pass_buffer, "\n")] = 0;
    if (read_ret == 0x29) {
        fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
        exit(1);
    }

    fclose(pwd_file);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");

    printf("--[ Username: ");
    fgets(username_buffer, 0x64, stdin);
    username_buffer[strcspn(username_buffer, "\n")] = 0;

    printf("--[ Password: ");
    fgets(pwd_buffer, 0x64, stdin);
    pwd_buffer[strcspn(pwd_buffer, "\n")] = 0;

    puts("*****************************************");
    if (!strncmp(pass_buffer, pwd_buffer, 0x29)) { // = 41
        printf(username_buffer);
        puts(" does not have access!");
        exit(1);
    }

    printf("Greetings, %s!\n", username_buffer);
    system("/bin/sh");
    
    return 0;
}