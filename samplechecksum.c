#include <stdio.h>

unsigned char calCheck(const char *data, size_t length)
{
    unsigned char checksum = 0;
    for(size_t i = 0; i <length; i++)
    {
        checksum += data[i];
    }
    return checksum;
}


int main(){
    const char data[] = "This code is written by kumail074";
    unsigned char checksum = calCheck(data, sizeof(data) - 1);
    printf("Checksum: %u\n", checksum);
    return 0;
    }

