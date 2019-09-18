#include <stdio.h>

int main() {
    int    i;

    char    char_arr[5] = "abcde";
    int     int_arr[5] = {1, 2, 3, 4, 5};

    char*   p_char;
    int*    p_int;

    p_char = int_arr;
    p_int =  char_arr;

    for (i = 0; i < 5; i++) {
        printf("[integer pointer] point out %p, contains num %c\n",
                p_int, *p_int);
        p_int++;
    }
    for (i = 0; i < 5; i++) {
        printf("[char pointer] point out %p, contains char %d\n",
                p_char, *p_char);
        p_char++;
    }
    return 0;
}
