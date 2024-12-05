#include <stdio.h>
#include <string.h>

int main(){
    char ops[4];
    int x=0;
    int i;
    scanf("%d",&i);
    while(i--){
        scanf("%s",&ops);
        if((strcmp(ops, "X++")==0) || (strcmp(ops, "++X")==0) || (strcmp(ops, "x++")==0) || (strcmp(ops, "++x")==0))
            x++;
        if((strcmp(ops, "X--")==0) || (strcmp(ops, "--X")==0) || (strcmp(ops, "x--")==0) || (strcmp(ops, "--x")==0))
            x--;
    }
    printf("%d\n",x);
    return 0;
}
