#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "hacking.h"

#define  FILENAME "notes"

int printNotes(int, int, char *);
int findUserNote(int, int);
int searchNote(char *, char *);
void fatal(char *);

int main(int argc, char *argv[]) {
    int userid, printing = 1, fd;
    char searchStr[100];

    if (argc > 1)
        strcpy(searchStr, argv[1]);
    else
        searchStr[0] = 0;

    userid = getuid();
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1)
        fatal("can't open file in main");

    while (printing)
        printing = printNotes(fd, userid, searchStr);
    printf("---------[end of node data]--------------------------------\n");
    close(fd);
}

int printNotes(int fd, int userid, char *searchStr) {
    int noteLen;
    char byte = 0, noteBuf[100];

    noteLen = findUserNote(fd, userid);
    if (noteLen == -1)
        return 0;

    read(fd, noteBuf, noteLen);
    noteBuf[noteLen] = 0;

    if (searchNote(noteBuf, searchStr))
        printf("%s", noteBuf);
    return 1;
}

int findUserNote(int fd, int userid) {
    int noteUid = -1;
    unsigned char byte;
    int len;

    while (noteUid != userid) {
        if (read(fd, &noteUid, 4) != 4) //reading uid
            return -1;
        if (read(fd, &byte, 1) != 1)
            return -1;

        byte = len = 0;
        while (byte != '\n') {
            if (read(fd, &byte, 1) != 1)
                return -1;
            len++;
        }
    }
    lseek(fd, len * -1, SEEK_CUR);

    printf("[DEBUG] find note with len %d byte for id %d\n", len, noteUid);
    return len;
}

int searchNote(char *note, char *keyword) {
    int i, keyWordLen, match = 0;

    keyWordLen = strlen(keyword);
    if (keyWordLen == 0)
        return -1;

    for (i = 0; i < strlen(note); i++) {
        if (note[i] == keyword[match])
            match++;
        else {
            if (note[i] == keyword[0])
                    match = 1;
            else
                match = 0;
        }
        if (match == keyWordLen)
            return 1;
    }
    return 0;
}
