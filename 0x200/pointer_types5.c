#include <stdio.h>

int main() {
    int    i;

    char    char_arr[5] = "abcde";
    int     int_arr[5] = {1, 2, 3, 4, 5};

    unsigned int h_nopointer;

    h_nopointer = (unsigned int)char_arr;
    for (i = 0; i < 5; i++) {
        printf("[integer pointer] point out %p, contains num %c\n",
                h_nopointer, *((char *)h_nopointer));
        h_nopointer = h_nopointer + sizeof(char);
    }
    h_nopointer = (unsigned int)int_arr;
    for (i = 0; i < 5; i++) {
        printf("[char pointer] point out %p, contains char %d\n",
              h_nopointer, *((int *)h_nopointer));
        h_nopointer = h_nopointer + sizeof(int);
    }
    return 0;
}
