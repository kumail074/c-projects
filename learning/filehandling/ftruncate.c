#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("file", O_RDWR);
    if(fd == -1){
        perror("open");
        return 1;
    }

    if (ftruncate(fd, 10) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    printf("file truncated\n");
    close(fd);
    return 0;
}
