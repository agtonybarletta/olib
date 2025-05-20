#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "heapq_i.h"
#include "heapq.h"


void HeapqI__for_each(HeapqI* self, void (*function)(int)) {
    for(unsigned long i = 0; i < self->_parent->size; i++) {
        function(*(int*)self->_parent->_buffer[i]);
    }
}


void HeapqI__insert(HeapqI* self, int i) {
    self->_parent->m->insert(self->_parent, &i);
    self->size =self->_parent->size;
}

int HeapqI__top(HeapqI* self) {
    int ret = *(int*)self->_parent->m->top(self->_parent);
    self->size =self->_parent->size;
    return ret;
    
}

HeapqIMethods HEAPQI_MRTHODS = {
    .insert = &HeapqI__insert,
    .top = &HeapqI__top,
    .for_each = &HeapqI__for_each
    
};

// Function pointer to store the compile-time function
static int (*wrapped_func)(int, int) = NULL;

// Wrapper function that calls the dynamically assigned function
int wrapper_add(void* a, void* b) {
    if (wrapped_func) {
        return wrapped_func(*(int*)a, *(int*)b);
    } else {
        printf("No function assigned!\n");
        return 0;
    }
}

// Function that assigns a function and returns the wrapper
int (*get_wrapper(int (*func)(void*, void*)))(int, int) {
    wrapped_func = func;  // Assign the function at "compile time"
    return wrapper_add;    // Return the wrapper function
}

HeapqI* HeapqI__init(int (*less_than)(int arg1, int arg2)) {
    HeapqI* self = malloc(sizeof(HeapqI));    
    if (self == NULL) {
        return self;
    }

    *self = (HeapqI) {
        ._parent = Heapq__init(get_wrapper(less_than)),
        .size = 0,
        .m = &HEAPQI_MRTHODS
    };
    return self;
}