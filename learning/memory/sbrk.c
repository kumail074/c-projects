#include "tlpi.h" //custom header defined in parent directory of this project
#include <unistd.h>
#define MAX 100000

int main(int argc, char *argv[]) {
    char *ptr[MAX];
    int freeStep, freeMin, freeMax, blockSize, numAllocs;
    if(argc < 3 || strcmp(argv[1], "--help") == 0) {
        perror("num-allocs");
        exit(EXIT_FAILURE);
    }

    numAllocs = getInt(argv[1], GN_GT_O, "num-allocs");
    if(numAllocs > MAX) {
        perror("num-allocs > MAX");
        exit(EXIT_FAILURE);
    }

    blockSize = getInt(argv[2], GN_GT_O | GN_ANY_BASE, "block-size");

    freeStep = (argc > 3) ? getInt(argv[3], GN_GT_O, "step") : 1;
    freeMin = (argc > 4) ? getInt(argv[4], GN_GT_O, "min") : 1;
    freeMax = (argc > 5) ? getInt(argv[5], GN_GT_O, "max") : numAllocs;

    if(freeMax > numAllocs) {
        perror("free-max > num-allocs\n");
        return 1;
    }
    printf("Initial break:      %10p\n", sbrk(0));
    printf("Allocating %d*%d bytes\n", numAllocs, blockSize);

    for(int j = 0; j < numAllocs; j++) {
        ptr[j] = malloc(blockSize);
        if(ptr[j] == NULL)
            exit(EXIT_FAILURE);
    }

    printf("Program break is now:       %10p\n", sbrk(0));
    printf("Freeing blocks from %d to %d in steps of %d\n", freeMin, freeMax, freeStep);
    for(int i = freeMin - 1; i < freeMax; i += freeStep)
        free(ptr[i]);

    printf("After free(), program break is: %10p\n", sbrk(0));
    exit(EXIT_SUCCESS);
}

