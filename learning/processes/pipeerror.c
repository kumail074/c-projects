#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

//simulated pipe error as it works usually
int main(){
    int fd[2];
    int count = 0;
    FILE *file[1024];
    while((file[count] = fopen("/dev/null", "r")) != NULL)
        count++;

    if(pipe(fd) == -1)
        perror("pipe failed");

    for(int i = 0; i < count; i++)
        fclose(file[i]);

    return 0;
}
