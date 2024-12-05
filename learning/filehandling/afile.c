#include <stdio.h>

int main(){
    FILE *fh = fopen("file.txt", "a"); //opens file in append mode
    fprintf(fh, "how are you eeqa?\n");
    fclose(fh);
    return 0;
}

