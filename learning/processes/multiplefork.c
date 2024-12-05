#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(){
    int id1 = fork();
    int id2 = fork();
    while(wait(NULL) != -1 || errno != ECHILD)
        printf("waiting for child process\n");

    if(id1 == 0)
    {
        if(id2 == 0)
            printf("grandchild\n");
        else
            printf("1st child of parent\n");
    } else {
        if(id2 == 0)
            printf("2nd child of parent\n");
        else
            printf("parent process\n");
    }
    return 0;
}
