#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void perror(const char *msg);

int main(){
    FILE *fd = fopen("file", "r");
    if(fd == NULL){
        perror("open");
        exit(EXIT_FAILURE);
    }
    return 0;
}
