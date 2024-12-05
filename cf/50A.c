#include <stdio.h>
#include <stdlib.h>

int main(){
    int m,n;
    scanf("%d %d",&m, &n);
    if(n%2==0) printf("%d\n", (m*n/2));
    else printf("%d\n", (m*(n/2)+(m/2)));
    return 0;
    }
