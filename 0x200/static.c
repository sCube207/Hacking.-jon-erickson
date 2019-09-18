#include <stdio.h>

void fuction() {
    int var = 5;
    static int staticVar = 5;
    
    printf("\t[we are in function] var = %d\n", var);
    printf("\t\t[we are in function] staticVal = %d\n", staticVar);
    var++;
    staticVar++;
}

int main() {
    int i;

    static int staticVar = 1337;

    for (i = 0; i < 5; i++) {
        printf("[main] staticVar = %d\n", staticVar);
        fuction();
    }
    return 0;
}
