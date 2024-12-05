#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

//void perror(const char *msg);
char *strerror(int errnum);


int main(){
    FILE *fd = fopen("file", "r");
    if(fd == NULL){
        printf("%s\n",strerror(errno));
        exit(EXIT_FAILURE);
    } else
        fclose(fd);
    return 0;
}
