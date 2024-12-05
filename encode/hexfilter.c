#include <stdio.h>

//simple hexadecimal filter
int main(){
    int c;
    while((c = getchar()) != EOF){
        printf("%02X", c);
    }
    putchar('\n');
    return 0;
}
