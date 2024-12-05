#include <stdio.h>

int tohex(char c){
    if(c >= '0' && c <= '9')
        return c - '0';
    if(c >= 'A' && c <= 'F')
        return c - 'A' + 0xA;
    return -1;
}


int main(){
    int c, a, b;

    while(1){
        c = getchar();
        if(c == EOF) break;
        a = tohex(c);
        if(a < 0) break;
        a <<= 4;
        c = getchar();
        if(c == EOF) break;
        b = tohex(c);
        if(b < 0) break;
        putchar(a+b);
    }
    putchar('\n');
    return 0;
}
