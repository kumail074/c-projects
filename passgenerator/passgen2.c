#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#define UP 1
#define LOW 6
#define NUM 1
#define SYM 2

int main(){
    char pass[UP+LOW+NUM+SYM+1];
    int x = 0;
    srand((unsigned)time(NULL));
    while(x<UP)
        pass[x++] = uppercase();
    while(x<UP+LOW)
        pass[x++] = lowercase();
    while(x<UP+LOW+NUM)
        pass[x++] = number();
    while(x<UP+LOW+NUM+SYM)
        pass[x++] = symbol();
    pass[x] = '\0';
    printf("%s\n", pass);
    return 0;
}
