#include <stdio.h>
#include <ctype.h>

int main(){
    int c;
    while((c=getchar())!=EOF){
        if(c == '-' || c == '.' || c == '_' || c == '*')
            putchar(c);
        else if(c == ' ')
            putchar('+');
        else if(isalnum(c))
            putchar(c);
        else
            printf("%%%02X",c);
    }
    return 0;
}
