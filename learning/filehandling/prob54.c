#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int mydup(int oldfd){
    int newfd = fcntl(oldfd, F_DUPFD, 0);
    if(newfd == -1)
        perror("mydup: fcntl");

    return newfd;
}

int mydup2(int oldfd, int newfd){
    if(fcntl(oldfd, F_GETFL) == -1){
        errno = EBADF;
        return -1;
    }

    if(oldfd == newfd)
        return newfd;

    if(fcntl(newfd, F_GETFL) != -1)
        close(newfd);

    int result = fcntl(oldfd, F_DUPFD, newfd);
    if(result == -1)
        perror("mydup2: fcntl");

    return result;
}

int main(){
    int fd = open("txt", O_RDWR | O_CREAT, 0644);
    if(fd == -1){
        perror("open");
        return 1;
    }

    int newfd = mydup(fd);
    if(newfd == -1)
        return 1;

    printf("duplicated fd using mydup: %d\n", newfd);

    int newfd2 = mydup2(fd, newfd);
    if(newfd2 == -1)
        return 1;

    printf("duplicated fd using mydup2: %d\n", newfd2);

    write(fd, "Original FD\n", 12);
    write(newfd, "mydup FD\n", 10);
    write(newfd2, "mydup2 FD\n", 11);

    close(fd);
    close(newfd);
    close(newfd2);

    return 0;
}
