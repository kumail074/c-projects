#include <stdio.h>
#include <ctype.h>

#define SIZE 64

int main(){
    char word[SIZE];
    int c, offset=0;

    while((c = getchar())!=EOF){
        if(isspace(c)){
            word[offset]='\0';
            if(offset>0)
                printf("%s\n",word);
            offset=0; }
        else {
            word[offset]=c;
            offset++;
            if(offset==SIZE-1){
                word[offset]='\0';
                printf("%s\n",word);
                offset=0;
            }
        }
    }
    return 0;
}
