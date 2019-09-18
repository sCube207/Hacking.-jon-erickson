#include <stdio.h>
#include <fcntl.h>

void displayFlags(char *, unsigned int);
void binaryPrint(unsigned int);

int main(int argc, char *argv[]) {
    displayFlags("O_RDONLY\t\t", O_RDONLY);
    displayFlags("O_WRONLY\t\t", O_WRONLY);
    displayFlags("O_RDWR\t\t\t", O_RDWR);
    printf("\n");
    displayFlags("O_APPEND\t\t", O_APPEND);
    displayFlags("O_TRUNC\t\t\t", O_TRUNC);
    displayFlags("O_CREAT\t\t\t", O_CREAT);
    printf("\n");
    displayFlags("O_WRONLY | O_APPEND | O_CREAT", O_WRONLY | O_APPEND | O_CREAT);
}

void displayFlags(char *label, unsigned int flags) {
    printf("%s\t: %d\t", label, flags);
    binaryPrint(flags);
    printf("\n");
}

void binaryPrint(unsigned int flags) {
    unsigned int mask = 0xff000000;
    unsigned int shift = 256 * 256 *256;
    unsigned int byte, byteIter, bitIter;

    for (byteIter = 0; byteIter < 4; byteIter++) {
        byte = (flags & mask) / shift;
        printf(" ");
        for (bitIter = 0; bitIter < 8; bitIter++) {
            if (byte & 0x80)
                printf("1");
            else
                printf("0");
            byte *= 2;
        }
        mask /= 256;
        shift /= 256;
    }

}
