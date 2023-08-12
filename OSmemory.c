#include <stdio.h>
#include <stdlib.h>

// Global variables
// Uninitialized global variables
char globalUninitialized1[20];
char globalUninitialized2[20];
// Initialized global variables
char globalInitialized1[20] = "globalInitialized1";
char globalInitialized2[20] = "globalInitialized2";
// Global pointer variables
char *globalMallocA = NULL;

int recurStackFunc(int to, int current) {
    printf("------------------------------\n");
    if (to == current) {
        return 0;
    }
    // Prove Stack grow downward
    char localA[16];
    int localB[16];
    printf("recurStackFunc: %d\n", current);
    printf("localA= %p\n", (void *)localA);
    printf("localB= %p\n", (void *)localB);
    if ((void *)localA > (void *)localB) {
        printf("localA > localB which means stack grow downward\n");
    } else {
        printf("localA < localB which means stack grow upward\n");
    }
    recurStackFunc(to, current + 1);
    return 0;
}

void main() {
    // to show address of global variables
    printf("========================================\nGlobal variables\n");
    printf("globalUninitialized1= %p\n", (void *)globalUninitialized1);
    printf("globalUninitialized2= %p\n", (void *)globalUninitialized2);
    printf("globalInitialized1= %p\n", (void *)globalInitialized1);
    printf("globalInitialized2= %p\n", (void *)globalInitialized2);
    globalMallocA = malloc(12 * sizeof(char));
    // Note: globalMallocA is point to heap memory, So globalMallocA <
    // globalUninitialized1 or globalUninitialized2
    printf("globalMallocA= %p\n", globalMallocA);
    free(globalMallocA);
    printf("========================================\nStack variables\n");
    recurStackFunc(3, 0);
}