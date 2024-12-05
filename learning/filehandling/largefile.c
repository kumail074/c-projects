#define _LARGEFILE64_SOURCE
#include <sys/stat.h>
#include <tlpi.h>
#include <fcntl.h>
//#include <errf.h>

void error(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int fd;
    off64_t off;

    if(argc != 3 || strcmp(argv[1], "--help") == 0)
        error("file offset");

    fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd == -1)
        error("open");

    off = atoll(argv[2]);
    if(lseek64(fd, off, SEEK_SET) == -1)
        error("lseek64");

    if(write(fd, "test", 4) == -1)
        error("write");

    exit(EXIT_SUCCESS);
}
