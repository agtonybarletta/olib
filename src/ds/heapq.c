#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "heapq.h"

int HEAPQ___INITIAL_BUFFER_SIZE = 256;
int HEAPQ___BUFFER_GROWTH_FACTOR = 2;

void Heapq__for_each(Heapq* self, void (*function)(void*)) {
    for(unsigned long i = 0; i < self->size; i++) {
        function(self->_buffer[i]);
    }
}

void Heapq___heapify_from(Heapq* self, unsigned long i) {
    if (i >= self->size) {
        printf("i out of bound");
        exit(-1);
    }
    if (i == 0) {
        return;
    }

    long parent = (i-1)/2;
    
    if (parent >= 0) {
        if (self->_less_than(self->_buffer[i], self->_buffer[parent]) > 0) {
            void* tmp = self->_buffer[i];
            self->_buffer[i] = self->_buffer[parent];
            self->_buffer[parent] = tmp;
            Heapq___heapify_from(self, parent);
        }
    }
}

void Heapq___heapify(Heapq* self) {
     Heapq___heapify_from(self, 0ul);
}



void Heapq___extend_buffer(Heapq* self) {
    
    if (self->_buffer_size * HEAPQ___BUFFER_GROWTH_FACTOR > ULONG_MAX) {
        printf("max size reached\n");
        exit(-1);
    }
    unsigned long new_buffer_size = self->_buffer_size *HEAPQ___BUFFER_GROWTH_FACTOR;
    void** new_buffer = calloc(new_buffer_size, sizeof(void*));
    memcpy(new_buffer, self->_buffer, self->_buffer_size);
    free(self->_buffer);
    self->_buffer = *new_buffer;
    self->_buffer_size = new_buffer_size;
}

void Heapq__insert(Heapq* self, void* object) {
    if (self->size == self->_buffer_size) {
        Heapq___extend_buffer(self);
    }
    
    self->size += 1;
    self->_buffer[self->size -1] = object;
    
    Heapq___heapify_from(self, self->size-1);
    
}

void* Heapq__top(Heapq* self) {
    
    void* top = self->_buffer[0ul];
    self->_buffer[0ul] = self->_buffer[self->size -1];
    self->size -= 1;
    Heapq___heapify_from(self, 0ul);
    return top;
    
}

HeapqMethods HEAPQ_MRTHODS = {
    .insert = &Heapq__insert,
    .top = &Heapq__top,
    .for_each = &Heapq__for_each
    
};

Heapq* Heapq__init(int (*less_than)(void* arg1, void* arg2)) {
    Heapq* self = malloc(sizeof(Heapq));    
    if (self == NULL) {
        return self;
    }
    
    *self = (Heapq) {
        ._buffer = malloc(sizeof(void*)*HEAPQ___INITIAL_BUFFER_SIZE),
        ._buffer_size = HEAPQ___INITIAL_BUFFER_SIZE,
        .size = 0,
        ._less_than = less_than,
        .m = &HEAPQ_MRTHODS
    };
    return self;
}