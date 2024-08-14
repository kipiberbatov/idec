#ifndef _array_indexed_h
#define _array_indexed_h

typedef struct array_indexed
{
  int * positions;
  int * values;
} array_indexed;

void array_indexed_merge_sort(array_indexed * a, int n);

#endif /* _array_indexed_h */
