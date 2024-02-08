#ifndef __ICE_ALLOCATOR__
#define __ICE_ALLOCATOR__

#include <stdlib.h>

typedef struct ice_allocator ice_allocator;

struct ice_allocator {
    void* (*alloc)(size_t bytes, void* context);
	void* (*realloc)(size_t bytes, void* ptr, void* context);
    void* (*free)(size_t bytes, void* ptr, void* context);
    void* context;
};

void* ice_alloc(size_t bytes, void* context) {
    (void)context;
    return malloc(bytes);
}

void* ice_realloc(size_t bytes, void* ptr, void* context) {
	(void)context;
	return realloc(ptr, bytes);
}

void* ice_free(size_t bytes, void* ptr, void* context) {
    (void)ptr;
	(void)context;
    free(ptr);
}

#endif // __ICE_ALLOCATOR__