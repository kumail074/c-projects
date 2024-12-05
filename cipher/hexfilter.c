#include <stdio.h>

int main(){
    int c;
    
    while((c = getchar()) != EOF){
        if( c == '\n')
            return 1;
        else
            printf("%X", c);   
    }
    putchar('\n');
    return 0;
}
