// simple english to nato
#include <stdio.h>
#include <ctype.h>

const char *nato[] = {          // you can replace these with your own alphabets
    "Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot",
"Golf", "Hotel", "India", "Juliett", "Kilo", "Lima",
"Mike", "November", "Oscar", "Papa", "Quebec", "Romeo",
"Sierra", "Tango", "Uniform", "Victor", "Whiskey",
"Xray", "Yankee", "Zulu" };

int main(){
    char phase[64];
    char ch;
    int i = 0;

    printf("input: ");
    fgets(phase, 64, stdin);

    while(phase[i]) {
        ch = toupper(phase[i]);
        if(isalpha(ch))
            printf("%s ",nato[ch - 'A']); //this gives us the corresponding index number e.g. 'C' - 'A' = 2 which means that index is 2 which isCharlie 
        i++;
        if(i == 64)
            break;
    }
    putchar('\n');
    return 0;
}
