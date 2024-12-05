#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main(){
    int x;
    char c;
    const int len = 10;
    srand((unsigned)time(NULL));
    for(x = 0; x<len; x++)
    {
        c = rand() % ('~' - '!' + 1);
        if(((c >= 'a' && c <='z') || (c >= 'A' && c <= 'Z')) && c % 3 == 0)
            putchar(toupper(c));
        else if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) && c % 2 == 0)
            putchar(tolower(c));
        else if (c % 6 == 0)
            printf("%d",c);
        else
            putchar(c);
    }
    putchar('\n');
    return 0;
}
