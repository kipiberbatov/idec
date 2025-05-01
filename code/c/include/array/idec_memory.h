#ifndef _idec_memory_h
#define _idec_memory_h

#include <stddef.h>

void idec_memory_allocate(void ** data, int * status, size_t size);
void idec_memory_allocate_zeros(void ** data, int * status, size_t size);
void idec_memory_reallocate(void ** new, int * status, void * old, size_t size);
void idec_memory_free(void * data);

#endif /* _idec_memory_h */
