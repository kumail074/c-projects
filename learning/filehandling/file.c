#include <stdio.h>

int main(){
    FILE *fh;
    fh = fopen("file.txt", "w"); //opens file in write mode (without append mode)
    fprintf(fh, "random content at %d\n", 54);
    fclose(fh);
    return 0;
}
