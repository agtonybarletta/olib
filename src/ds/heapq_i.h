#include "heapq.h"

typedef struct HeapqI {
    int (*_less_than)(int, int);
    unsigned long size;
    Heapq* _parent;
    struct HeapqIMethods* m;
} HeapqI;

typedef struct HeapqIMethods {
    void (*heapify)(struct HeapqI*);
    void (*insert)(struct HeapqI*, int);
    int (*top)(struct HeapqI*);
    void (*for_each)(struct HeapqI*, void function(int));
} HeapqIMethods;

HeapqI* HeapqI__init(int (*less_than)(int arg1, int arg2));