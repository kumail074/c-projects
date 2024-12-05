#include <stdio.h>
#include <stdlib.h>
char *binstr(char a){
    static char b[9];
    int i = 0;
    while(i<8)
    {
        b[i] = a&0x80 ? '1' : '0';
        a <<= 1;
        i++;
    }
    b[i] = '\0';
    return b;
}

int main(){
    char p = 5;
    char *n = binstr(p);
   /* for(int i = 0; i<3; i++){
        n = binstr(p[i]);
        printf("%c ", *n);
    } */ 
    printf("%d: %s\n", p, n);  
    putchar('\n');
    return 0;
}
