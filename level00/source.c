#include <stdio.h>
#include <stdlib.h>

int main() {
    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");

    printf("Password:");

    int result;
    scanf("%d", &result);

    if (result == 0x149c) { // 5276
        puts("\nAuthenticated!");
        system("/bin/sh");
        return 0;
    }
    puts("\nInvalid Password!");
    return 1;
}