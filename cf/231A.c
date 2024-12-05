#include <stdio.h>

int main(){
    int l, a, b, c, ans=0;
    scanf("%d\n",&l);
    while(l--){
        scanf("%d %d %d", &a, &b, &c);
        int y=0;
        if(a == 1) y++;
        if(b == 1) y++;
        if(c == 1) y++;
        
        if(y>1) ans++;
    }
    printf("%d\n",ans);
    return 0;
}
