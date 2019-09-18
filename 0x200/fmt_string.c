#include <stdio.h>
#include <string.h>

int main() {
    char str[10];
    char A = -73;
    unsigned int B = 31337;
    
    strcpy(str, "sample");
    printf("[A] Dec %d, Hex %x, unsigned %u\n", A, A, A);
    printf("[B] Dec %d, Hex %x, unsigned %u\n", B, B, B);
    printf("[fill length B] 3 - %3u, 10 - %10u, %08u\n", B, B, B);
    printf("[string] %s adress %8p\n", str, str);
    printf("value of A by adress %8p\n", &A);
}
