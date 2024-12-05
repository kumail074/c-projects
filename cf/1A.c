#include <stdio.h>
#include <math.h>

int main(){
    unsigned long m, n, a;
    scanf("%lu %lu %lu\n", &m, &n, &a);

    unsigned long total = (unsigned long)ceil((double)m/a)*(unsigned long)ceil((double)n/a);

    printf("%lu\n", total);
    return 0;
}
