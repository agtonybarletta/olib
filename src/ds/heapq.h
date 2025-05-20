typedef struct Heapq {
    unsigned long size;
    void** _buffer;
    unsigned long _buffer_size;
    int (*_less_than)(void*, void*);
    struct HeapqMethods* m;
} Heapq;

typedef struct HeapqMethods {
    void (*insert)(struct Heapq*, void*);
    void* (*top)(struct Heapq*);
    void (*for_each)(struct Heapq*, void function(void*));
} HeapqMethods;

Heapq* Heapq__init(int (*less_than)(void* arg1, void* arg2));