void fatal(char *msg) {
    char errorMsg[100];

    strcpy(errorMsg, "[!!] Critical error");
    strncat(errorMsg, msg, 80);
    perror(errorMsg);
    exit(-1);
}

void *ecMalloc(unsigned int size) {
    void *p;
    p = malloc(size);
    if (p == NULL)
        fatal("can't allocate memory in ecMalloc\n");
    return p;
}
