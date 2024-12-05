#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

//simulated fork errors/failures as fork usually works
int main(){
    int forkcount = 0;
    while(1){
        int pid = fork();
        if(pid == -1){
            perror("fork failed");
            break;
        }
        else if(pid == 0)
            _exit(0); //make each child process exit immediately
        else {
            forkcount++;
        }
    }
    printf("total forks: %d\n", forkcount);
    return 0;
}

