#include <stdio.h>

int main(){
    int c;

    while((c = getchar()) != EOF){
        if (c > 96 && c < 123)
            c = c - 32;
        
        putchar(c);
    }
    return 0;
}

