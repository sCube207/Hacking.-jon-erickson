#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *pChar;
    int *pInt;
    int memSize;

    if (argc < 2)
        memSize = 50;
    else
        memSize = atoi(argv[1]);

    printf("\t[+] alloced %d bytes in the heap for var pChar\n",memSize);
    pChar = (char *)malloc(memSize);

    if (pChar == NULL) {
        fprintf(stderr, "error: can't alloc memory\n");
        exit(-1);
    }

    strcpy(pChar, "This memory is located in the heap");
    printf("pChar (%p) --> '%s'\n", pChar, pChar);

    printf("\t[+] allocated 12 bytes in the heap for pInt\n");
    pInt = (int *)malloc(12);

    if (pInt == NULL) {
        fprintf(stderr, "error: can't alloc memory\n");
        exit(-1);
    }

    *pInt = 31337;
    printf("pInt (%p) --> '%d'\n", pInt, *pInt);

    printf("\t[-] free memory\n");
    free(pChar);

    printf("\t[+] allocated 15 bytes in the heap for pChar\n");
    pChar = (char *)malloc(15);

    if (pChar == NULL) {
        fprintf(stderr, "error: can't alloc memory\n");
        exit(-1);
    }

    strcpy(pChar, "new memory");
    printf("pChar (%p) --> '%s'\n", pChar, pChar);

    printf("\t[-] free memory\n");
    free(pChar);

    printf("\t[-] free memory\n");
    free(pInt);
    return 0;
}
