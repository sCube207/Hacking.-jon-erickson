#include <stdio.h>
#include <string.h>

int main() {
    char msg[13];
    int cout, i;

    strcpy(msg, "Hello world!");
    
    printf("Enter the cout\n");
    scanf("%d", &cout);

    for (i = 0; i < cout; i++)
        printf("%d - %s\n", i, msg);
    return 0;
}
