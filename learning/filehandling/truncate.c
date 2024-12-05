#include <unistd.h>
#include <stdio.h>

int main() {
    const char *file = "file";

    if(truncate(file, 100) == -1){
        perror("truncate");
        return 1;
    }

    printf("file truncated successfully.\n");
    return 0;
}
