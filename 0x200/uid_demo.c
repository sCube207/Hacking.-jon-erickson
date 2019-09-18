#include <stdio.h>

int main() {
    printf("real uid: %d\n", getuid());
    printf("fake uid: %d\n", geteuid());
}
