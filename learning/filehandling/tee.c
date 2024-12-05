#include <tlpi.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER 1024

int append = 0;
int igint = 0;

void handlesignal(int sig){
    if(igint){
        printf("\nInterrupt ignored. Use 'kill' to terminate.\n");
    } else {
        exit(sig);
    }
}

int main(int argc, char *argv[]) {
    char buffer[BUFFER];
    ssize_t numread;
    int i, outfd;

    for(i = 1; i < argc && argv[i][0] == '-'; i++){
        if(strcmp(argv[i], "-a") == 0){
            append = 1;
        } else if (strcmp(argv[i], "-i") == 0) {
            igint = 1;
            signal(SIGINT, handlesignal);
        } else {
            fprintf(stderr, "Usage %s [-a] [-i] [file...]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    int numfiles = argc - i;
    int fds[numfiles];
    for(int j = 0; j < numfiles; j++){
        if(append){
            fds[j] = open(argv[i+j], O_WRONLY | O_CREAT | O_APPEND, 0644);
        } else {
            fds[j] = open(argv[i + j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }

        if(fds[j] == -1){
            perror("open");
            exit(EXIT_FAILURE);
        }
    }

    while((numread = read(STDIN_FILENO, buffer, BUFFER)) > 0) {
        if(write(STDOUT_FILENO, buffer, numread) != numread) {
            perror("write to stdout");
            exit(EXIT_FAILURE);
        }

        for(int j = 0; j < numfiles; j++) {
            if(write(fds[j], buffer, numread) != numread){
                perror("write to file");
                exit(EXIT_FAILURE);
            }
        }
    }

    if(numread == -1){
        perror("read");
        exit(EXIT_FAILURE);
    }

    for(int j = 0; j < numfiles; j++){
        if(close(fds[j]) == -1){
            perror("close");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

