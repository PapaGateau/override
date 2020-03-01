#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
    uint32_t i = 0;
    uint8_t buffer[0x64]; // 100

    fgets(buffer, 0x64, stdin);
    while (i < strlen(buffer)) {
        if (buffer[i] > 64 && buffer[i] <= 90) {
            buffer[i] ^= 0x20;
        }
        i++;
    }
    printf(buffer);
    exit(0);
}