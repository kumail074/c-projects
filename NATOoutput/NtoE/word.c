#include <stdio.h>
#include <string.h>

int main(){
    char text[64];
    char *match;
    printf("enter text: ");
    fgets(text, 64, stdin);

    match = strtok(text, " ");
    while(match){
        printf("%s\n", match);
        match = strtok(NULL, " ");
    }
    return 0;
}
