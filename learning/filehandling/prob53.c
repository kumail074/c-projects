#include <tlpi.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void usage(const char *prog){
    fprintf(stderr, "Usage: %s filename num-bytes [x]\n", prog);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
    if(argc < 3 || argc > 4){
        usage(argv[0]);
    }

    const char *file = argv[1];
    int numbytes = atoi(argv[2]);
    int uselseek = (argc = 4 && strcmp(argv[3], "x") == 0);

    int fd = open(file, O_WRONLY | O_CREAT | (uselseek ? 0 : O_APPEND), 0644);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    char byte = 'a';

    for(int i = 0; i < numbytes; i++){
        if(uselseek){
            if(lseek(fd, 0, SEEK_END) == -1){
                perror("lseek");
                close(fd);
                exit(EXIT_FAILURE);
            }
        }

        if(write(fd, &byte, 1) != 1){
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    close(fd);
    return 0;
}
