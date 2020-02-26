#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    uint32_t ac = argc; // RBP - 0x94
    uint64_t av = argv; // RBP - 0xa0
    uint64_t var0 = fs(0x28); // WTF is that // RBP - 0x8
    uint8_t var1 = 255; // RBP - 0x71
    int32_t var2 = -1; // RBP - 0x78
    
    if (ac != 2) {
        printf("Usage: %s filename\n");
    }
    FILE *open_ret;
    if (!(open_ret = fopen("./backups/.log", "w"))) {
        printf("ERROR: Failed to open%s\n", "./backups/.log");
    }

}