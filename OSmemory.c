#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------------------------------- */
/*                              Global variables                              */
/* -------------------------------------------------------------------------- */
// Uninitialized global variables
char globalUninitialized1[20];
char globalUninitialized2[20];
// Initialized global variables
char globalInitialized1[20] = "globalInitialized1";
char globalInitialized2[20] = "globalInitialized2";
// Global pointer variables
char *globalMallocA = NULL;

/* -------------------------------------------------------------------------- */
/*                                    Stack                                   */
/* -------------------------------------------------------------------------- */
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
int isStackGrowDownward() {
    char localA[16];
    int localB[16];
    if ((void *)localA > (void *)localB) {
        return 1;
    } else {
        return 0;
    }
}
int isStackGrowDownwardOverflow(int number) {
    if (number == 0) {
        return 0;
    }
    char localA[16];
    int localB[16];
    if ((void *)localA > (void *)localB) {
        return isStackGrowDownwardOverflow(number - 1) + 1;
    } else {
        return 0;
    }
}
int testStackGrowDownward(int number) {
    int option = 0;
    printf(
        "Chose Option for Testing Stack\n(0):not Stack-Overflow\n"
        "(1):Stack-Overflow :\n");
    scanf("%d", &option);
    printf("Test stack grow downward: ");
    if (option == 0) {
        // Test stack grow downward with for loop
        for (int i = 0; i < number; i++) {
            if (!isStackGrowDownward()) {
                printf("False at %d\n", i);
                return 0;
            }
        }
        printf("Correct for %d times\n", number);
        printf("------------------------------\n");
        return 1;
    } else if (option == 1) {
        // Test stack grow downward with recursion
        int result = isStackGrowDownwardOverflow(number);
        if (result != number) {
            printf("False at %d\n", result);
            return 0;
        } else {
            printf("Correct for %d times\n", number);
            printf("------------------------------\n");
            return 1;
        }
    }
}
/* -------------------------------------------------------------------------- */
/*                                    Heap                                    */
/* -------------------------------------------------------------------------- */
void recurHeapFunc(int number) {
    printf("------------------------------\n");
    if (number == 0) {
        return;
    }
    // Prove Heap grow from low address
    char *localMallocA = malloc(12 * sizeof(char));
    int *localMallocB = malloc(12 * sizeof(int));
    printf("localMallocA= %p\n", localMallocA);
    printf("localMallocB= %p\n", localMallocB);
    if ((void *)localMallocA < (void *)localMallocB) {
        printf("localMallocA < localMallocB which means heap grow upward\n");
    } else {
        printf("localMallocA > localMallocB which means heap grow downward\n");
    }
    recurHeapFunc(number - 1);
    free(localMallocA);
    free(localMallocB);
}
int isHeapGrowUpward() {
    char *localMallocA = malloc(12 * sizeof(char));
    int *localMallocB = malloc(12 * sizeof(int));
    if ((void *)localMallocA < (void *)localMallocB) {
        return 1;
    } else {
        return 0;
    }
}
int isHeapGrowUpwardOverflow(int number) {
    if (number == 0) {
        return 0;
    }
    char *localMallocA = malloc(12 * sizeof(char));
    int *localMallocB = malloc(12 * sizeof(int));
    if ((void *)localMallocA < (void *)localMallocB) {
        return isHeapGrowUpwardOverflow(number - 1) + 1;
    } else {
        return 0;
    }
}
int testHeapGrowUpward(int number) {
    int option = 0;
    printf(
        "Chose Option for Testing Heap\n(0):not Heap-Overflow\n"
        "(1):Heap-Overflow :\n");
    scanf("%d", &option);
    printf("Test Heap grow Upward: ");
    if (option == 0) {
        // Test Heap grow Upward with for loop
        for (int i = 0; i < number; i++) {
            if (!isHeapGrowUpward()) {
                printf("False at %d\n", i);
                return 0;
            }
        }
        printf("Correct for %d times\n", number);
        printf("------------------------------\n");
        return 1;
    } else if (option == 1) {
        // Test Heap grow Upward with recursion
        int result = isHeapGrowUpwardOverflow(number);
        if (result != number) {
            printf("False at %d\n", result);
            return 0;
        } else {
            printf("Correct for %d times\n", number);
            printf("------------------------------\n");
            return 1;
        }
    }
}
int TestTimes = 10000000;
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
    // To show address of stack variables and prove stack grow downward
    printf("========================================\nStack variables\n");
    recurStackFunc(3, 0);
    testStackGrowDownward(TestTimes);
    // To show address of heap variables and prove heap grow upward
    printf("========================================\nHeap variables\n");
    recurHeapFunc(3);
    testHeapGrowUpward(TestTimes);
}