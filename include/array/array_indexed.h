#ifndef ARRAY_INDEXED_H
#define ARRAY_INDEXED_H

typedef struct array_indexed
{
  int * positions;
  int * values;
} array_indexed;

void array_indexed_merge_sort(array_indexed * a, int n);

#endif /* ARRAY_INDEXED_H */
