#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
    int arr[9] = {4,6,1,5,7,2,6,0,3};
    int fd[2];
    int start, end;
    int arrsize = sizeof(arr)/sizeof(int);
    if(pipe(fd) == -1){
        perror("pipe failed");
        return 1; }
    int id1 = fork();
    if(id1 == -1){
        perror("fork failed");
        return 1; }

    
    return 0;
}
