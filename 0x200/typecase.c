#include <stdio.h>

int main() {
    int a, b;
    float c, d;

    a = 13;
    b = 5;

    c = a / b;
    d = (float) a / b;

    printf("int c %f\n", c);
    printf("float d %f\n", d);

}
