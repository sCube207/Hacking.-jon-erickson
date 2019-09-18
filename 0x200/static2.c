#include <stdio.h>

void fuction() {
    int var = 5;
    static int staticVar = 5;
    
    printf("\t[function] var @ %p = %d\n", &var, var);
    printf("\t\t[we are in function] staticVal @ %p = %d\n",
            &staticVar, staticVar);
    var++;
    staticVar++;
}

int main() {
    int i;

    static int staticVar = 1337;

    for (i = 0; i < 5; i++) {
        printf("[main] staticVar @ %p = %d\n", &StaticVar, staticVar);
        fuction();
    }
    return 0;
}
