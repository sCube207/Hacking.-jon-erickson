#include <stdio.h>
#include <stdlib.h>

void usage(char *progName) {
    printf("Usage: %s <massage> <# of times to repeat>\n", progName);
    exit(1);
}

int main(int argc, char *argv[]) {
    int i, count;

    //if (argc < 3)
        //usage(argv[0]);

    count = atoi(argv[2]);
    printf("Reapeat %d times\n", count);

    for (i = 0; i < count; i++)
        printf("%3d - %s\n", i, argv[1]);
    return 0;
}
