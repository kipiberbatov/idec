#ifndef _cmc_memory_h
#define _cmc_memory_h

#include <stddef.h>

void cmc_memory_allocate(void ** data, int * status, size_t size);
void cmc_memory_allocate_zeros(void ** data, int * status, size_t size);
void cmc_memory_reallocate(void ** new, int * status, void * old, size_t size);
void cmc_memory_free(void * data);

#endif /* _cmc_memory_h */
