#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd, fddup;
    char buffer[100];

    fd = open("txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }

    write(fd, "areeqa\n", 8);

    fddup = dup(fd);
    if(fddup == -1){
        perror("dup");
        close(fd);
        exit(EXIT_FAILURE);
    }

    lseek(fd, 7, SEEK_SET);

    ssize_t bytes = read(fddup, buffer, sizeof(buffer) - 1);
    if(bytes == -1){
        perror("read");
        close(fd);
        close(fddup);
        exit(EXIT_FAILURE);
    }
    buffer[bytes] = '\0';
    printf("data read from duplicated fd: %s\n", buffer);

    int flags = fcntl(fddup, F_GETFL);
    if(flags == -1){
        perror("fcntl - F_GETFL");
        close(fd);
        close(fddup);
        exit(EXIT_FAILURE);
    }

    if(fcntl(fddup, F_SETFL, flags | O_APPEND) == -1){
        perror("fcntl - F_SETFL");
        close(fd);
        close(fddup);
        exit(EXIT_FAILURE);
    }
    
    flags = fcntl(fd, F_GETFL);
    if(flags & O_APPEND) {
        printf("O_APPEND flag is set on original fd.\n");
    } else {
        printf("O_APPEND flag is not set on original fd.\n");
    }

    close(fd);
    close(fddup);

    return 0;
}
