#include <stdio.h>
#include <string.h>

int main() {
    char str_a[20];
    char *p1;
    char *p2;

    strcpy(str_a, "Hello world!\n");
    p1 = str_a;
    printf("%s", p1);

    p2 = p1 + 2;
    printf("%s", p2);
    strcpy(p2, "y you guys!\n");
    printf("%s", p1);
    return 0;
}
