#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#include "ds/heapq.h"

int less_than(int* a, int* b) {
    if (*a < *b) {
        return 1;
    } else if (*a == *b){
        return 0;
    } else {
        return -1;
    }
}

void print(int* a) {
    printf("%d, ", *a);
}

int main() {

    Heapq* heapq = Heapq__init((int (*)(void*, void*))&less_than);
    
    printf("Heapq size: %lu\n", heapq->size);
    
   
#define N 12 
    int a[N] = {};
    struct timeval tp;

    gettimeofday(&tp, NULL);
    int seed = (int)tp.tv_usec;
    srand(seed);

    for (int i = 0; i < N; i++) {
        a[i] = rand() %227;
        heapq->insert(heapq, (void*)&a[i]);
    }

    printf("Heapq size: %lu\n", heapq->size);
    printf("Heapq: ");
    heapq->for_each(heapq, (void (*)(void*))&print);
    


    return 0;
}