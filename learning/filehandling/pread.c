#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int fd = open("copy", O_RDONLY);
    if(fd == -1){
        perror("failed to open file");
        return 1;
    }
    char buffer[50];
    ssize_t bytes = pread(fd, buffer, sizeof(buffer) - 1, 50);
    if(bytes == -1){
        perror("pread failed");
        close(fd);
        return 1;
    }
    buffer[bytes] = '\0';
    printf("read data: %s\n", buffer);
    close(fd);
    return 0;
}
