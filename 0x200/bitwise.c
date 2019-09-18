#include <stdio.h>

int main() {
    int i, bitA, bitB;

    printf("binary operation OR |\n");
    for (i = 0; i < 4; i++) {
        bitA = (i & 2) / 2;
        bitB = (i & 1);
        printf("%d | %d = %d\n", bitA, bitB, bitA | bitB);
    }
    printf("binary operation AND &\n");
    for (i = 0; i < 4; i++) {
        bitA = (i & 2) / 2;
        bitB = (i & 1);
        printf("%d & %d = %d\n", bitA, bitB, bitA & bitB);
    }
}
