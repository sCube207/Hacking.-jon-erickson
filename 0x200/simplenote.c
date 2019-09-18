#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void usage(char *progName, char *fileName) {
    printf("Usage: %s <data to add to %s>\n", progName, fileName);
    exit(0);
}

void fatal(char *);
void *ecMalloc(unsigned int);

int main(int argc, char *argv[]) {
    int fd;
    char *buffer, *datafile;

    buffer = (char *)ecMalloc(100);
    datafile = (char *)ecMalloc(20);
    strcpy(datafile, "./notes");

    if (argc < 2)
        usage(argv[0], datafile);

    strcpy(buffer, argv[1]);

    printf("[DEBUG] buffer @ %p: \'%s'\n", buffer, buffer);
    printf("[DEBUG] datafile @ %p: \'%s'\n", datafile, datafile);

    strncat(buffer, "\n", 1);

//open a file
    fd = open(datafile, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    if (fd == -1)
        fatal("error: can't open file\n");
    printf("[DEBUG] descriptor of file %d\n", fd);
//write data
    if (write(fd, buffer, strlen(buffer)) == -1)
        fatal("error: can't write data\n");
//close file
    if (close(fd) == -1)
        fatal("error: can't close file\n");
    printf("Note saved.\n");
    free(buffer);
    free(datafile);
}

void fatal(char *msg) {
    char errorMsg[100];

    strcpy(errorMsg, "[!!]Critical error");
    strncat(errorMsg, msg, 80);
    perror(errorMsg);
    exit(-1);
}

void *ecMalloc(unsigned int size) {
    void *p;

    p = malloc(size);
    if (p == NULL)
        fatal("error: can't allocate memory\n");
    return p;
}






