// coverting  files
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]){

    const char *nato[] = {
        "Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot",
"Golf", "Hotel", "India", "Juliett", "Kilo", "Lima",
"Mike", "November", "Oscar", "Papa", "Quebec", "Romeo",
"Sierra", "Tango", "Uniform", "Victor", "Whiskey",
"Xray", "Yankee", "Zulu" };
    FILE *f;
    int ch;

    if (argc < 2) {
        fprintf(stderr, "it is not a text argument\n");
        exit(1); }

    f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "unable to open '%s'\n", argv[1]);
        exit(1); }

    while((ch = fgetc(f)) != EOF){
        if(isalpha(ch))
            printf("%s ", nato[toupper(ch) - 'A']);
    }

    putchar('\n');
    fclose(f);
    return 0;
}
