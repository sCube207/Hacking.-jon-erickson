#include <stdio.h>

int main() {
    int int_var = 5;
    int *int_ptr;

    int_ptr = &int_var;

    printf("int_ptr = %8p\n", int_ptr);
    printf("&int_ptr = %8p\n", &int_ptr);
    printf("*int_ptr = 0x%08x\n\n", *int_ptr);

    printf("Adress of int_var is %8p and it contains %d\n", &int_var,int_var);
    printf("Adress of int_ptr is %8p, it contains adress %8p and it points out %d\n", &int_ptr, int_ptr, *int_ptr);
    return 0;
}
