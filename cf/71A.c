#include <stdio.h>
#include <string.h>

int main(){
    char word[101];
    int l,i;
    scanf("%d\n", &i);
    while(i--){
        scanf("%s",&word);
        l = strlen(word);
        if(l>10)
            printf("%c%d%c\n",word[0],l-2,word[l-1]);
        else
            printf("%s\n",word);
    }
    return 0;
}

