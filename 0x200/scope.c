#include <stdio.h>

void func3() {
    int i = 11;
    printf("\t\t\t[we are in the func3] i = %d\n", i);
}

void func2() {
    int i = 7;
    printf("\t\t[we are in the func2] i = %d\n", i);
    func3();
    printf("\t\t[back to func2] i = %d\n", i);
}

void func1() {
    int i = 5;
    printf("\t[we are in the func1] i = %d\n", i);
    func2();
    printf("\t[back to func1] i = %d\n", i);
}

int main() {
    int i = 3;
    printf("[we are in the main] i = %d\n", i);
    func1();
    printf("[back to main] i = %d\n", i);
}
