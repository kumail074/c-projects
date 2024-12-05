#include <stdio.h>

int main(){

    printf("Dec\tHex\tC\n");
    for(int i = 0; i < 256; i++)
        printf("%d\t%02X\t%c\n", i, i, i);
    return 0;
}
