#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// in this, the replacing value is incremented by 1 (by default) or some number user enters
int main(){
    int c,n;
    printf("enter number: ");
    scanf("%d\n", &n);
    srand(rand());
    while((c = getchar()) != EOF)
    {
        if(isalpha(c)){
            if (toupper(c) >= 'A' && toupper(c) <= 'M')
                c += n;
            else
                c -= n;
        }
        putchar(c);
    }
    return 0;
}
