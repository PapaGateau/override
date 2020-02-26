#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void set_msg(char *buffer, int32_t *buffer_size) {
    char new_buff[400];

    memset(new_buff, '\0', 0x80); // 128
    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    fgets(new_buff, 0x400, stdin);
    strncpy(buffer, new_buff, *buffer_size); // 0x8c ; 140
}

void set_username(char *buffer) {
    int32_t i;
    char new_buff[144];
    
    bzero(new_buff, 16);
    puts(">: Enter your username");
    printf(">>: ");
    fgets(new_buff, 0x80, stdin);
    *(int32_t *)(new_buff + 140) = 0;
    i = 0;
    while (i <= 0x28 && new_buff[i]) {
        buffer[i + 140] = new_buff[i];
        i++;
    }
    printf(">: Welcome, %s", buffer + 140);
}

void handle_msg() {
    
    char buffer[180]; //inaccurate, its likely bigger
    int32_t buffer_size = 180; // placed right after buffer in memory
    set_username(buffer);
    set_msg(buffer, &buffer_size);
}

int main() {
    puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n--------------------------------------------");
    handle_msg();
    return 0;
}