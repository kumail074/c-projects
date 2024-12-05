//preadv and pwritev
#include <tlpi.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/uio.h>

int main() {
    int fd = open("file", O_RDONLY);
    if(fd == -1){
        perror("open");
        return 1;
    }

    char b1[20], b2[10];
    struct iovec iov[2];

    iov[0].iov_base = b1;
    iov[0].iov_len = sizeof(b1);
    iov[1].iov_base = b2;
    iov[1].iov_len = sizeof(b2);

    ssize_t bytes = preadv(fd, iov, 2, 0);
    if(bytes == -1){
        perror("preadv");
        return 1;
    }

    printf("Read %zd bytes: %.*s%.*s\n", bytes, (int)sizeof(b1), b1, (int)sizeof(b2), b2);
    close(fd);
    return 0;
}
