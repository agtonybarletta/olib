typedef struct Heapq {
    void (*heapify)(struct Heapq*);
    void (*insert)(struct Heapq*, void*);
    void (*for_each)(struct Heapq*, void function(void*));
    unsigned long size;
    void** _buffer;
    unsigned long _buffer_size;
    int (*_less_than)(void*, void*);
} Heapq;

Heapq* Heapq__init(int (*less_than)(void* arg1, void* arg2));