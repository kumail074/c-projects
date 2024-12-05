#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bpl 18
#define length (bpl*3+1)

int main(){
    char *r;
    char line[length];
    int   hex;

    while(1){
        r = fgets(line, length, stdin);
        if(r == NULL || strncmp(line, "HEX ENCODE", 10) != 0){
            fprintf(stderr, "invalide HEX ENCODE data\n");
            exit(1); }
        if(strncmp(line, "HEX ENCODE END", 13)==0)
            break;
        r = strtok(line, " ");
        while(r){
            sscanf(r, "%02X", &hex);
            printf("%c",hex);
            r = strtok(NULL, " "); }
    }

    return 0;
}










        /*if(c == '\n' || x == length){
            if(line[x-1]=='\n')
                line[x-1] = '\0';
            else
                line[x] = '\0';

            printf("%s\n", line);
            x = 0;
        }*/
    //}
  //  return 0;
//}
