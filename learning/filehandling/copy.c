#include <sys/stat.h>
#include <fcntl.h>
#include <tlpi.h>
#include "errf.h"

#ifndef BUFSIZE
#define BUFSIZE 1024
#endif

int main(int argc, char *argv[]) {
    int infd, outfd, openflags;
    mode_t fileperms;
    ssize_t numread;
    char buf[BUFSIZE];

    if(argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s old-file new-file\n", argv[0]);
    infd = open(argv[1], O_RDONLY);
    if(infd == -1)
        errExit("opening file %s\n", argv[1]);

    openflags = O_CREAT | O_WRONLY | O_EXCL;
    fileperms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    outfd = open(argv[2], openflags, fileperms);
    if(outfd == -1)
        errExit("opening file %s\n", argv[2]);
   
    while(((numread = read(infd, buf, BUFSIZE)) > 0) && ((numread = read(infd, buf, BUFSIZE)) <= BUFSIZE) )
        if(write(outfd, buf, numread) != numread)
            fatal("couldn't write whole buffer\n");
    if(numread == -1)
        perror("read\n");

    if(close(infd) == -1)
        perror("close input\n");
    if(close(outfd) == -1)
        perror("close output\n");

    exit(EXIT_SUCCESS);
}
