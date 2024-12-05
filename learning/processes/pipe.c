#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//void perror(const char *msg);

int main(){
    int fd[2]; //file descriptors i.e. read and write
     if(pipe(fd) == -1){
         perror("pipe creation error");
         return 1;
     }
     int id = fork();
     if(id == -1) {
          perror("fork failed");
          return 1;
     }
     if(id == 0){ //child process code - passing value to parent process
         close(fd[0]); //reading end
         int x;
         printf("enter a number: ");
         scanf("%d", &x);
         if(write(fd[1], &x, sizeof(int)) == -1){
             printf("error occured writing to the pipe\n");
             return 2;
         }
         close(fd[1]); //writing end
     } else { //parent process code - reading value from child process
        close(fd[1]); //writing end 
        int y;
        if(read(fd[0], &y, sizeof(int)) == -1){
            printf("error occured reading from the pipe\n");
            return 2;
        }
        close(fd[0]); //reading end
        printf("got value from child process %d\n", y);
     }
     return 0;
     }
