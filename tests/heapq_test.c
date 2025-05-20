#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#include "heapq.h"

#define N 12 

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
    
   
    int a[N] = {};
    struct timeval tp;

    gettimeofday(&tp, NULL);
    int seed = (int)tp.tv_usec;
    srand(seed);

    for (unsigned int i = 0; i < N; i++) {
        a[i] = rand() %227;
        heapq->m->insert(heapq, (void*)&a[i]);
    }

    printf("Heapq size: %lu\n", heapq->size);
    printf("Heapq: ");
    heapq->m->for_each(heapq, (void (*)(void*))&print);
    printf("\n");

    
    int max_a = -1;
    int min_a = 256;
    for (int i = 0; i < N; i++){
        if (a[i] < min_a) {
            min_a = a[i];
        }
        if (a[i] > max_a) {
            max_a = a[i];
        }
    }
    
    int* heap_min = heapq->m->top(heapq);
    
    if (*heap_min != min_a) {
        printf("Assert failed, got %d, expected %d\n", *heap_min, min_a);
        exit(-1);
    }
    for (int i = 0; i < (N-2); i++) {
        heapq->m->top(heapq);
    }
    int* heap_max = heapq->m->top(heapq);

    if (*heap_max != max_a) {
        printf("Assert failed, got %d, expected %d\n", *heap_max, max_a);
        exit(-1);
    }

    return 0;
}