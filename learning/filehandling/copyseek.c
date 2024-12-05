#include <tlpi.h> //custom header file which includes most of the standard header files
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER 4096


//program like cp that, when used to copy a regular file that contains holes (sequences of null bytes), also creates corresponding holes in the target file.
int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage %s <source> <destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sfd = open(argv[1], O_RDONLY);
    if(sfd == -1){
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }
    
    int dfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 644);
    if(dfd == -1) {
        perror("Error opening destination file");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER];
    ssize_t bytes;

    while((bytes = read(sfd, buffer, BUFFER)) > 0){
        for(ssize_t i = 0; i < bytes;) {
            ssize_t start = i;
            while(start < bytes && buffer[start] != '\0')
                start++;

            if(start > i){
                if(write(dfd, &buffer[i], start - i) != start - i) {
                    close(sfd);
                    close(dfd);
                    perror("Error writing to destination file");
                }
            }

            ssize_t end = start;
            while(end < bytes && buffer[end] == '\0')
                    end++;
            
            if(end > start) {
                if(lseek(dfd, end - start, SEEK_CUR) == -1) {
                    close(sfd);
                    close(dfd);
                    perror("Error seeking in destination file");
                }
            }

            i = end;
        }
    }

    if(bytes == -1) {
        close(sfd);
        close(dfd);
        perror("Error reading from source file");
    }

    close(sfd);
    close(dfd);
    return 0;
}
