#include <stdio.h>

int main(){
    FILE *fh;
    fh = fopen("file.txt", "r"); //opens file in read mode
    char str[100];
    while(fscanf(fh, "%s", &str) != EOF){
    fscanf(fh, "%s", &str); 
    printf("%s\n", str); }
    fclose(fh);
    return 0;
}
