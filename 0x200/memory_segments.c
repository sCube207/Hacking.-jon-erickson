#include <stdio.h>
#include <stdlib.h>

int globalVal;
int globalInitVar = 5;

void fuction() {
    int stackVar;

    printf("stackVar has addres %p\n", &stackVar);
}

int main() {
    int stackVar;
    static int staticInitVar;
    static int staticVar;
    int *heapVarPtr;

    heapVarPtr = (int *) malloc(4);

//this varibles are in initialized segment of memory
    printf("globalInitVar has addres %p\n", &globalInitVar);
    printf("staticInitVar has addres %p\n\n", &staticInitVar);

//this varibles are in no initialized segment of memyry
    printf("staticVar has addres %p\n", &staticVar);
    printf("globalVal has addres %p\n\n", &globalVal);

//this varible is in heap
    printf("heapVarPtr has addres %p\n\n", heapVarPtr);

//this varible in the stack
    printf("stackVarPtr has addres %p\n\n", &stackVar);
    fuction();
    return 0;
}
