#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int value = 5;
    char buffer_one[8], buffer_two[8];

    strcpy(buffer_one, "one");
    strcpy(buffer_two, "two");

    printf("[Before] buffer_two with addres %p contains \'%s\'\n",
            buffer_two, buffer_one);
    printf("[Before] buffer_one with addres %p contains \'%s\'\n",
            buffer_one, buffer_one);
    printf("[Before] value with addres %p contains \'%d\'\n",
            &value, value);
    printf("\n[STRCPY] copy %lu bytes to buffer_two\n\n", strlen(argv[1]));
    strcpy(buffer_two, argv[1]);

    printf("[After] buffer_two with addres %p contains \'%s\'\n",
            buffer_two, buffer_two);
    printf("[After] buffer_one with addres %p contains \'%s\'\n",
            buffer_one, buffer_one);
    printf("[After] value with addres %p contains \'%d\'\n",
            &value, value);
}
