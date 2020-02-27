#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");

    printf("Password:");

    int result;
    scanf("%d", &result);

    if (result == 0x149c) {
        puts("\nAuthenticated!");
        system("/bin/sh");
        return 0;
    }
    puts("\nInvalid Password!");
    return 1;
}