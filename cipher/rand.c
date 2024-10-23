#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main(){
    int c;
    srand(rand());
    while((c = getchar()) != EOF)
    {
        if(isalpha(c)){
            if(rand() % 3 == 0)
                c = toupper(c);
            else
                c = tolower(c);
        }
        putchar(c);
    }
    return 0;
}
