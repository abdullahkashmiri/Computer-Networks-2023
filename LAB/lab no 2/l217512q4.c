//21L-7512 Abdullah dar CN lab 2 Q4

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    short num = 0x3412;
    unsigned char *ptr = (unsigned char *)&num;
    if (*ptr == 0x12) {
        printf("Machine is Little Endian\n");
    } else if (*ptr == 0x34) {
        printf("Machine is Big Endian\n");
    } else {
        printf("Byte ordering could not be determined\n");
    }
    printf("Bytes in memory:\n");
    for (int i = 0; i < sizeof(short); i++) {
        printf("Byte %d: 0x%02x\n", i, *ptr);
        ptr++;  
    }

    return 0;
}