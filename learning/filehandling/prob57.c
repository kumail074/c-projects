#include <unistd.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <tlpi.h>
#include <errno.h>
ssize_t myreadv(int fd, const struct iovec *iov, int iovcnt) {
    ssize_t totalread = 0;

    for(int i = 0; i < iovcnt; i++) {
        size_t len = iov[i].iov_len;
        char *buffer = (char *) iov[i].iov_base;

        ssize_t numread = read(fd, buffer, len);
        if(numread == -1){
            perror("read");
            return -1;
        }
        totalread += numread;

        if(numread < len){
            break;
        }
    }

    return totalread;
}

ssize_t mywritev(int fd, const struct iovec *iov, int iovcnt){
    ssize_t totalwritten = 0;

    for(int i = 0; i < iovcnt; i++) {
        size_t len = iov[i].iov_len;
        const char *buffer = (const char *) iov[i].iov_base;

        ssize_t numwritten = write(fd, buffer, len);
        if(numwritten == -1){
            perror("write");
            return -1;
        }

        totalwritten += numwritten;

        if(numwritten < len){
            break;
        }
    }

    return totalwritten;
}

int main() {
    char *b1 = malloc(10);
    char *b2 = malloc(20);
    char *b3 = malloc(30);

    if(!b1 || !b2 || !b3) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    struct iovec iov[3];
    iov[0].iov_base = b1;
    iov[0].iov_len = sizeof(b1);
    iov[1].iov_base = b2;
    iov[1].iov_len = sizeof(b2);
    iov[2].iov_base = b3;
    iov[2].iov_len = sizeof(b3);

    int fd = open("txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    ssize_t bytes = myreadv(fd, iov, 3);
    if(bytes == -1){
        perror("myreadv");
        return EXIT_FAILURE;
    }
    printf("total bytes read: %zd\n", bytes);

    printf("bufer1: %.*s\n", (int)iov[0].iov_len, (char *)iov[0].iov_base);
    printf("buffer2: %.*s\n", (int)iov[1].iov_len, (char *)iov[1].iov_base);
    printf("buffer3: %.*s\n", (int)iov[2].iov_len, (char *)iov[2].iov_base);

    ssize_t wbytes = mywritev(fd, iov, 3);
    if(wbytes == -1) {
        perror("mywritev");
        return EXIT_FAILURE;
    }
    printf("bytes written: %zd\n", wbytes);

    free(b1);
    free(b2);
    free(b3);
    close(fd);

    return EXIT_SUCCESS;
}
