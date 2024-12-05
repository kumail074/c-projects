#include <stdio.h>
#include <string.h>

char isNato(char *word){
   const char *nato[] = {
        "Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot",
"Golf", "Hotel", "India", "Juliett", "Kilo", "Lima",
"Mike", "November", "Oscar", "Papa", "Quebec", "Romeo",
"Sierra", "Tango", "Uniform", "Victor", "Whiskey",
"Xray", "Yankee", "Zulu" };
    int i;
    char *n, *t;

    for(i = 0; i < 26; i++){
        n = nato[i];
        t = word;
        while(*n != '\0'){
            if ( (*n&0x20) != (*t&0x20))  // covert each letter to uppercase using bitwise operation when used with & operator, and upper case to lower case if | operator is used e.g. *n|0x20
                break;
            n++;
            t++; }
        if (*n == '\0')
            return *nato[i];
    }
    return '\0';
}

int main(){
    char ch, snc[64];
    char *match;

    printf("NATO phrase: ");
    fgets(snc, 64, stdin);

    match = strtok(snc, " "); // used to split the sentence into words
    while(match){
        if ((ch=isNato(match)) != '\0')
            putchar(ch);
        match = strtok(NULL, " ");
    }
    putchar('\n');
    return 0;
}
