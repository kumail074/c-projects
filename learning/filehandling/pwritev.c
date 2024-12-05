#include <tlpi.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>

int main() {
    int fd = open("file", O_WRONLY | O_CREAT, 0644);
    if(fd == -1) {
        perror("open");
        return 1;
    }

    char b1[] = "are";
    char b2[] = "eqa";
    char b3[] = "\n";

    struct iovec iov[3];

    iov[0].iov_base = b1;
    iov[0].iov_len = sizeof(b1) - 1;
    iov[1].iov_base = b2;
    iov[1].iov_len = sizeof(b2) - 1;
    iov[2].iov_base = b3;
    iov[2].iov_len = sizeof(b3) - 1;
    
    ssize_t bytes = pwritev(fd, iov, 3, 0);
    if(bytes == -1){
        perror("pwritev");
        return 1;
    }

    printf("wrote %zd bytes\n", bytes);
    close(fd);
    return 0;
}
