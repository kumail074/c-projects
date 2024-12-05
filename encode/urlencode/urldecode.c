#include <stdio.h>

int tohex(int c);

int main()
{
    int a, b, c;
    while((c = getchar()) != EOF){
        if(c == '%')
        {
            c = getchar();
            if(c == EOF) break;
            a = tohex(c);
            c = getchar();
            if(c == EOF) break;
            b = tohex(c);
            putchar((a<<4)+b);
        }
        else
            putchar(c);
    }
    return 0;
}

int tohex(int c)
{
    if(c >= '0' && c <= '9')
        return c - '0';
    if(c >= 'A' && c <= 'F')
        return c - 'A' + 0xA;
    if(c >= 'a' && c <= 'z')
        return c = 'a' + 0xA;
    return -1;
}
