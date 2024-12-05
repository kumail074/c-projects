#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <tlpi.h>
#include "errf.h"
#include "getnum.h"
int main(int argc, char *argv[]) {
    size_t len;
    off_t offset;
    int fd, ap, j;
    char *buf;
    ssize_t numread, numwrite;

    if(argc < 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n", argv[0]);
    fd = open(argv[1], O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if(fd == -1)
        errExit("open");

    for(ap = 2; ap < argc; ap++){
        switch(argv[ap][0]) {
            case 'r':
            case 'R':
                len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
                buf = malloc(len);
                if(buf == NULL)
                    errExit("malloc");

                numread = read(fd, buf, len);
                if(numread == -1)
                    errExit("read");

                if(numread == 0){
                    printf("%s: EOF\n", argv[ap]);
                } else {
                    printf("%s: ", argv[ap]);
                    for(j = 0; j < numread; j++){
                        if(argv[ap][0] == 'r')
                            printf("%c", isprint((unsigned char) buf[j]) ? buf[j] : '?');
                        else
                            printf("%02x ", (unsigned int) buf[j]);
                    }
                    printf("\n");
                }
                free(buf);
                break;

            case 'w':
                numwrite = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
                if(numwrite == -1)
                    errExit("write");
                printf("%s: wrote %ld bytes\n", argv[ap], (long) numwrite);
                break;
            case 's':
                offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
                if(lseek(fd, offset, SEEK_SET) == -1)
                    errExit("lseek");
                printf("%s: seek succeeded\n", argv[ap]);
                break;
            default:
                cmdLineErr("argument must start with [rRws]: %s\n", argv[ap]);
        }
    }

    exit(EXIT_SUCCESS);
}
