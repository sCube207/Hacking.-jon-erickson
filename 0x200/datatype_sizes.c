#include <stdio.h>

int main() {
    printf("Lenght of 'int' is\t\t %lu bytes\n", sizeof(int));
    printf("Lenght of 'unsigned int' is \t %lu bytes\n", sizeof(unsigned int));
    printf("Length of 'short int' is \t %lu bytes\n", sizeof(short int));
    printf("Length of 'long int' is \t %lu bytes\n", sizeof(long int));
    printf("Length of 'long long int' is \t %lu bytes\n", sizeof(long long int));
    printf("Length of 'float' is \t\t %lu bytes\n", sizeof(float));
    printf("Length of 'char' is \t\t %lu bytes\n", sizeof(char));
    return 0;
}
