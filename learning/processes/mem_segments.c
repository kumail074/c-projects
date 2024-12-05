#include <stdio.h>
#include <stdlib.h>

char buf[65536]; // uninitialized data segment
int primes[] = {2, 3, 5, 7, 11}; // initialized data segment

static int square(int x) {
    int result;     //allocated in frame for square
    result = x * x;
    return result;  // return value passed via register
}

static void doCalc(int val) { //allocated in frame for doCalc
    printf("Square of %d is %d\n", val, square(val));

    if(val < 1000) {
        int t = val * val * val;
        printf("Cube is %d\n", t);
    }
}

int main(int argc, char *argv[]) {
    static int key = 8974;    //initialized data segment
    static char mbuf[10240000]; //uninitialized data segment
    char *p; //allocated in frame for main
    p = malloc(1024); //points to memory in heap
    doCalc(key);
    exit(EXIT_SUCCESS);
}
