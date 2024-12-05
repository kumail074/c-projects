#define _GNU_SOURCE
#include <tlpi.h>

extern char **environ;

int main(int argc, char *argv[]) {
 
    char **ep;

    clearenv();
    for(int j = 1; j < argc; j++) {
        if(putenv(argv[j]) != 0) {
            perror("Putenv");
            exit(EXIT_FAILURE);
        }
    }

    if(setenv("GREET", "Hey Patch", 0) == -1){
        perror("setenv");
        return 1;
    }

    unsetenv("danke");
    for(ep = environ; *ep != NULL; ep++)
        puts(*ep);

    exit(EXIT_SUCCESS);
}
