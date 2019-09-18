#include <stdio.h>

int main() {
    int    i;

    char    char_arr[5] = "abcde";
    int     int_arr[5] = {1, 2, 3, 4, 5};

    void *p_void;

    p_void = (void *)char_arr;
    for (i = 0; i < 5; i++) {
        printf("[integer pointer] point out %p, contains num %c\n",
                p_void, *((char *)p_void));
        p_void = (void *)((char *)p_void + 1);
    }
    for (i = 0; i < 5; i++) {
        printf("[char pointer] point out %p, contains char %d\n",
                p_void, *((int *)p_void));
        p_void =(void *)((int *)p_void + 1);
    }
    return 0;
}
