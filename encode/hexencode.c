#include <stdio.h>
#define bpl 18

int main(){
    int c, byte=0, checksum = 0;
    printf("HEX ENCODE v2.0\n");
    while((c=getchar())!=EOF){
        printf("%02X ", c);
        byte++;
        if(byte == bpl){
            printf(" checksum: %02X", checksum);
            putchar('\n');
            byte=0; }
        checksum += c;
    }
    printf("\nHEX ENCODE END\n");
    return 0;
}
