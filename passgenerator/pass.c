#include <stdio.h>
#include <string.h>

void increment(char *str);

int main(){
    char guess[9] = "aaaaaaaa";
    const char pass[] = "password";
    while(strcmp(guess, pass) != 0) {
        increment(guess);
    }
    printf("Password found: %s\n", guess);
    return 0;
}

void increment(char *str){
    int i = strlen(str) - 1;
    while(i >= 0) {
        if(str[i] < 'z') {
            str[i]++;
            return;
        } else {
            str[i] = 'a';
            i--; }
    }
}
