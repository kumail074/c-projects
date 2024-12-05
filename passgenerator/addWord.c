#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define repeat(a) for(int x=0;x<a;x++)

const char *add(void){
    const char *voc[] = {
        "orange", "grape", "apple", "banana",
    "coffee", "tea", "juice", "beverage",
    "happy", "grumpy", "bashful", "sleepy" };
    int r = rand() % (sizeof(voc)/sizeof(char *));
    return voc[r];
}

int main(){
    srand((unsigned)time(NULL));
    repeat(3)
        printf("%s ", add());
    putchar('\n');
    return 0;
}
