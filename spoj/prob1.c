// TEST - Life, the Universe, and the Everything
#include <stdio.h>
#include <ctype.h>
int main(){
    int c;
    while(1){
        scanf("%d", &c);
        if (c == 42)
            break;

        printf("%d\n", c);
    }
    return 0;
}

