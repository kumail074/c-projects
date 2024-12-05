#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// in this, the replacing value is incremented by 1 (by default) or some number user enters
int main(){
    int c,sh;
    char a, b;
    printf("enter characters: ");
    scanf("%c\t%c\n", &a, &b);
    sh = a - b;
    while((c = getchar()) != EOF)
    {
        if(isalpha(c)){
            if(isupper(c)){
                c+=sh;
                if(c > 'Z') c-=26;
                if(c < 'A') c+=26;
                putchar(c);
                    }
            else if(islower(c)) {
                c+=sh;
                if(c > 'z') c-=26;
                if(c < 'a') c+=26;
                putchar(c);
                }
           else
              putchar(c); }
    }
    return 0;
}
