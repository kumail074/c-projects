#include <tlpi.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd = open("copy", O_WRONLY);
    if(fd == -1)
        perror("failed to open file");

    const char *data = "/*sample data*/";
    ssize_t bytes = pwrite(fd, data, 15, 10);
    if(bytes == -1){
        perror("pwrite failed");
        close(fd);
    }

    printf("data written successfully\n");
    close(fd);
    return 0;
}
