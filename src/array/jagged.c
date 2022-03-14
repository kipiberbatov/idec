#include <stdlib.h>
#include "array_fprint.h"
//#include "array_print.h"
#include "int.h"
#include "jagged.h"
#include "list.h"

/********************************** jagged1 ***********************************/
void jagged1_set(jagged1 * arr, int arr_a0, int * arr_a1)
{
  arr->a0 = arr_a0;
  arr->a1 = arr_a1;
}

jagged1 * jagged1_new(int arr_a0, int * arr_a1)
{
  jagged1 * arr;
  
  arr = (jagged1 *) malloc(sizeof(jagged1));
  /* NULL pointer check */
  arr->a0 = arr_a0;
  arr->a1 = arr_a1;
  return arr;
}

int jagged1_part1(const jagged1 * arr, int i1)
{
  /* if (i1 < 0 || i1 >= arr->a0) return -1; */
  return arr->a1[i1];
}

// void jagged1_print(const jagged1 * arr)
// {
//   array_print1(arr->a0, arr->a1);
// }

void jagged1_fprint(FILE * out, const jagged1 * arr)
{
  array_fprint1(out, arr->a0, arr->a1);
}

void jagged1_fprint_annotated(
  FILE * out, const jagged1 * arr, const char * name)
{
  fputs(name, out);
  fputs(" = ", out);
  jagged1_fprint(out, arr);
  fputs("\n\n", out);
}

void jagged1_fprint_raw(FILE * out, const jagged1 * arr)
{
  int arr_a0;
  int * arr_a1;
  
  arr_a0 = arr->a0;
  arr_a1 = arr->a1;
  fprintf(out, "%d\n", arr_a0);
  int_fprint_array_raw(out, arr_a0, arr_a1);
}

jagged1 * jagged1_fscan_raw(FILE * in)
{
  int arr_a0;
  int * arr_a1;
  jagged1 * arr;
  
  fscanf(in, "%d", &arr_a0);
  /* successfull scanning check */
  arr_a1 = int_fscan_array(in, arr_a0);
  /* NULL pointer and successfull scanning check */
  arr = jagged1_new(arr_a0, arr_a1);
  /* NULL pointer check */
  return arr;
}

void jagged1_free(jagged1 * arr)
{
  free(arr->a1);
  free(arr);
}

jagged1 * jagged1_complement(int n, const jagged1 * arr)
{
  int i, j, ind;
  jagged1 * res;
  
  res = (jagged1 *) malloc(sizeof(jagged1));
  res->a0 = n - arr->a0;
  res->a1 = (int *) malloc(res->a0 * sizeof(int));
  
  ind = 0;
  i = 0;
  j = 0;
  while (j < arr->a0)
  {
    if (i == arr->a1[j])
    {
      ++i;
      ++j;
    }
    else
    {
      res->a1[ind] = i;
      ++i;
      ++ind;
    }
  }
  while (i < n)
  {
    res->a1[ind] = i;
    ++i;
    ++ind;
  }
  return res;
}

/********************************** jagged2 ***********************************/
void jagged2_set(jagged2 * arr, int arr_a0, int * arr_a1, int * arr_a2)
{
  arr->a0 = arr_a0;
  arr->a1 = arr_a1;
  arr->a2 = arr_a2;
}

jagged2 * jagged2_new(int arr_a0, int * arr_a1, int * arr_a2)
{
  jagged2 * arr;
  
  arr = (jagged2 *) malloc(sizeof(jagged2));
  /* NULL pointer check */
  arr->a0 = arr_a0;
  arr->a1 = arr_a1;
  arr->a2 = arr_a2;
  return arr;
}

void jagged2_part1(jagged1 * res, const jagged2 * arr, int i1)
{
  int p2;
  /* if (i1 < 0 || i1 >= arr->a0) return -1; */
  p2 = list_sum(arr->a1, 0, i1);
  jagged1_set(res, arr->a1[i1], arr->a2 + p2);
}

int jagged2_part2(const jagged2 * arr, int i1, int i2)
{
  int p2;
  /* if (i1 < 0 || i1 >= arr->a0) return -1; */
  /* if (i2 < 0 || i2 >= arr->a1[i1]) return -1; */
  p2 = list_sum(arr->a1, 0, i1);
  return arr->a2[p2 + i2];
}

void jagged2_fprint(FILE * out, const jagged2 * arr)
{
  array_fprint2(out, arr->a0, arr->a1, arr->a2);
}

// void jagged2_print(const jagged2 * arr)
// {
//   array_print2(arr->a0, arr->a1, arr->a2);
// }

void jagged2_fprint_annotated(
  FILE * out, const jagged2 * arr, const char * name)
{
  fputs(name, out);
  fputs(" = ", out);
  jagged2_fprint(out, arr);
  fputs("\n\n", out);
}

void jagged2_fprint_raw(FILE * out, const jagged2 * arr)
{
  int arr_a0, arr_a2_size;
  int * arr_a1, * arr_a2;
  
  arr_a0 = arr->a0;
  arr_a1 = arr->a1;
  arr_a2 = arr->a2;
  fprintf(out, "%d\n", arr_a0);
  int_fprint_array_raw(out, arr_a0, arr_a1);
  arr_a2_size = list_sum(arr_a1, 0, arr_a0);
  int_fprint_array_raw(out, arr_a2_size, arr_a2);
}

jagged2 * jagged2_fscan_raw(FILE * in)
{
  int arr_a0, arr_a2_size;
  int * arr_a1, * arr_a2;
  jagged2 * arr;
  
  fscanf(in, "%d", &arr_a0);
  /* successfull scanning check */
  arr_a1 = int_fscan_array(in, arr_a0);
  /* NULL pointer and successfull scanning check */
  arr_a2_size = list_sum(arr_a1, 0, arr_a0);
  arr_a2 = int_fscan_array(in, arr_a2_size);
  /* NULL pointer and successfull scanning check */
  arr = jagged2_new(arr_a0, arr_a1, arr_a2);
  /* NULL pointer check */
  return arr;
}

void jagged2_free(jagged2 * arr)
{
  free(arr->a2);
  free(arr->a1);
  free(arr);
}

/********************************** jagged3 ***********************************/
void jagged3_set(jagged3 * arr, int arr_a0, int * arr_a1, int * arr_a2,
                 int * arr_a3)
{
  arr->a0 = arr_a0;
  arr->a1 = arr_a1;
  arr->a2 = arr_a2;
  arr->a3 = arr_a3;
}

jagged3 * jagged3_new(int arr_a0, int * arr_a1, int * arr_a2, int * arr_a3)
{
  jagged3 * arr;
  
  arr = (jagged3 *) malloc(sizeof(jagged3));
  /* NULL pointer check */
  arr->a0 = arr_a0;
  arr->a1 = arr_a1;
  arr->a2 = arr_a2;
  arr->a3 = arr_a3;
  return arr;
}

void jagged3_part1(jagged2 * res, const jagged3 * arr, int i1)
{
  int p2, p3;
  /* if(i1 < 0 || i1 >= arr->a0) return -1; */
  p2 = list_sum(arr->a1, 0, i1);
  p3 = list_sum(arr->a2, 0, p2);
  jagged2_set(res, arr->a1[i1], arr->a2 + p2, arr->a3 + p3);
}

void jagged3_part2(jagged1 * res, const jagged3 * arr, int i1, int i2)
{
  int p2, p3;
  /* if (i1 < 0 || i1 >= arr->a0) return -1; */
  /* if (i2 < 0 || i2 >= arr->a1[i1]) return -1; */
  p2 = list_sum(arr->a1, 0, i1);
  p3 = list_sum(arr->a2, 0, p2 + i2);
  jagged1_set(res, arr->a2[p2 + i2], arr->a3 + p3);
}

int jagged3_part3(const jagged3 * arr, int i1, int i2, int i3)
{
  int p2, p3;
  /*if (i1 < 0 || i1 >= arr->a0) return -1; */
  /* if (i2 < 0 || i2 >= arr->a1[i1]) return -1; */
  p2 = list_sum(arr->a1, 0, i1);
  /* if (i3 < 0 || i3 >= arr->a2[p2 + i2]) return -1; */
  p3 = list_sum(arr->a2, 0, p2 + i2);
  return arr->a3[p3 + i3];
}

void jagged3_fprint(FILE * out, const jagged3 * arr)
{
  array_fprint3(out, arr->a0, arr->a1, arr->a2, arr->a3);
}

// void jagged3_print(const jagged3 * arr)
// {
//   array_print3(arr->a0, arr->a1, arr->a2, arr->a3);
// }

void jagged3_fprint_annotated(
  FILE * out, const jagged3 * arr, const char * name)
{
  fputs(name, out);
  fputs(" = ", out);
  jagged3_fprint(out, arr);
  fputs("\n\n", out);
}

void jagged3_fprint_raw(FILE * out, const jagged3 * arr)
{
  int arr_a0, arr_a2_size, arr_a3_size;
  int * arr_a1, * arr_a2, * arr_a3;
  
  arr_a0 = arr->a0;
  arr_a1 = arr->a1;
  arr_a2 = arr->a2;
  arr_a3 = arr->a3;
  fprintf(out, "%d\n", arr_a0);
  int_fprint_array_raw(out, arr_a0, arr_a1);
  arr_a2_size = list_sum(arr_a1, 0, arr_a0);
  int_fprint_array_raw(out, arr_a2_size, arr_a2);
  arr_a3_size = list_sum(arr_a2, 0, arr_a2_size);
  int_fprint_array_raw(out, arr_a3_size, arr_a3);
}

jagged3 * jagged3_fscan_raw(FILE * in)
{
  int arr_a0, arr_a2_size, arr_a3_size;
  int * arr_a1, * arr_a2, * arr_a3;
  jagged3 * arr;
  
  fscanf(in, "%d", &arr_a0);
  /* successfull scanning check */
  arr_a1 = int_fscan_array(in, arr_a0);
  /* NULL pointer and successfull scanning check */
  arr_a2_size = list_sum(arr_a1, 0, arr_a0);
  arr_a2 = int_fscan_array(in, arr_a2_size);
  /* NULL pointer and successfull scanning check */
  arr_a3_size = list_sum(arr_a2, 0, arr_a2_size);
  arr_a3 = int_fscan_array(in, arr_a3_size);
  /* NULL pointer and successfull scanning check */
  arr = jagged3_new(arr_a0, arr_a1, arr_a2, arr_a3);
  /* NULL pointer check */
  return arr;
}

void jagged3_free(jagged3 * arr)
{
  free(arr->a3);
  free(arr->a2);
  free(arr->a1);
  free(arr);
}

/********************************** jagged4 ***********************************/
void jagged4_set(jagged4 * arr, int arr_a0, int * arr_a1, int * arr_a2,
                 int * arr_a3, int * arr_a4)
{
  arr->a0 = arr_a0;
  arr->a1 = arr_a1;
  arr->a2 = arr_a2;
  arr->a3 = arr_a3;
  arr->a4 = arr_a4;
}

jagged4 * jagged4_new(int arr_a0, int * arr_a1, int * arr_a2, int * arr_a3,
                      int * arr_a4)
{
  jagged4 * arr;
  
  arr = (jagged4 *) malloc(sizeof(jagged4));
  /* NULL pointer check */
  arr->a0 = arr_a0;
  arr->a1 = arr_a1;
  arr->a2 = arr_a2;
  arr->a3 = arr_a3;
  arr->a4 = arr_a4;
  return arr;
}

void jagged4_part1(jagged3 * res, const jagged4 * arr, int i1)
{
  int p2, p3, p4;
  /* if (i1 < 0 || i1 >= arr->a0) return -1; */
  p2 = list_sum(arr->a1, 0, i1);
  p3 = list_sum(arr->a2, 0, p2);
  p4 = list_sum(arr->a3, 0, p3);
  jagged3_set(res, arr->a1[i1], arr->a2 + p2, arr->a3 + p3, arr->a4 + p4);
}

void jagged4_part2(jagged2 * res, const jagged4 * arr, int i1, int i2)
{
  int p2, p3, p4;
  /* if (i1 < 0 || i1 >= arr->a0) return -1; */
  /* if (i2 < 0 || i2 >= arr->a1[i1]) return -1; */
  p2 = list_sum(arr->a1, 0, i1);
  p3 = list_sum(arr->a2, 0, p2 + i2);
  p4 = list_sum(arr->a3, 0, p3);
  jagged2_set(res, arr->a2[p2 +i2], arr->a3 + p3, arr->a4 + p4);
}

void jagged4_part3(jagged1 * res, const jagged4 * arr, int i1, int i2, int i3)
{
  int p2, p3, p4;
  /* if (i1 < 0 || i1 >= arr->a0) return -1; */
  /* if (i2 < 0 || i2 >= arr->a1[i1])  return -1; */
  p2 = list_sum(arr->a1, 0, i1);
  /* if (i3 < 0 || i3 >= arr->a2[p2 + i2]) return -1; */
  p3 = list_sum(arr->a2, 0, p2 + i2);
  p4 = list_sum(arr->a3, 0, p3 + i3);
  jagged1_set(res, arr->a3[p3 + i3], arr->a4 + p4);
}

int jagged4_part4(const jagged4 * arr, int i1, int i2, int i3, int i4)
{
  int p2, p3, p4;
  /* if (i1 < 0 || i1 >= arr->a0) return -1; */
  /* if (i2 < 0 || i2 >= arr->a1[i1])  return -1; */
  p2 = list_sum(arr->a1, 0, i1);
  /* if (i3 < 0 || i3 >= arr->a2[p2 + i2]) return -1; */
  p3 = list_sum(arr->a2, 0, p2 + i2);
  /* if (i4 < 0 || i4 >= arr->a3[p3 + i3]) return -1; */
  p4 = list_sum(arr->a3, 0, p3 + i3);
  return arr->a4[p4 + i4];
}

void jagged4_fprint(FILE * out, const jagged4 * arr)
{
  array_fprint4(out, arr->a0, arr->a1, arr->a2, arr->a3, arr->a4);
}

// void jagged4_print(const jagged4 * arr)
// {
//   array_print4(arr->a0, arr->a1, arr->a2, arr->a3, arr->a4);
// }

void jagged4_fprint_annotated(
  FILE * out, const jagged4 * arr, const char * name)
{
  fputs(name, out);
  fputs(" = ", out);
  jagged4_fprint(out, arr);
  fputs("\n\n", out);
}

void jagged4_fprint_raw(FILE * out, const jagged4 * arr)
{
  int arr_a0, arr_a2_size, arr_a3_size, arr_a4_size;
  int * arr_a1, * arr_a2, * arr_a3, * arr_a4;
  
  arr_a0 = arr->a0;
  arr_a1 = arr->a1;
  arr_a2 = arr->a2;
  arr_a3 = arr->a3;
  arr_a4 = arr->a4;
  fprintf(out, "%d\n", arr_a0);
  int_fprint_array_raw(out, arr_a0, arr_a1);
  arr_a2_size = list_sum(arr_a1, 0, arr_a0);
  int_fprint_array_raw(out, arr_a2_size, arr_a2);
  arr_a3_size = list_sum(arr_a2, 0, arr_a2_size);
  int_fprint_array_raw(out, arr_a3_size, arr_a3);
  arr_a4_size = list_sum(arr_a3, 0, arr_a3_size);
  int_fprint_array_raw(out, arr_a4_size, arr_a4);
}

jagged4 * jagged4_fscan_raw(FILE * in)
{
  int arr_a0, arr_a2_size, arr_a3_size, arr_a4_size;
  int * arr_a1, * arr_a2, * arr_a3, * arr_a4;
  jagged4 * arr;
  
  fscanf(in, "%d", &arr_a0);
  /* successfull scanning check */
  arr_a1 = int_fscan_array(in, arr_a0);
  /* NULL pointer and successfull scanning check */
  arr_a2_size = list_sum(arr_a1, 0, arr_a0);
  arr_a2 = int_fscan_array(in, arr_a2_size);
  /* NULL pointer and successfull scanning check */
  arr_a3_size = list_sum(arr_a2, 0, arr_a2_size);
  arr_a3 = int_fscan_array(in, arr_a3_size);
  /* NULL pointer and successfull scanning check */
  arr_a4_size = list_sum(arr_a3, 0, arr_a3_size);
  arr_a4 = int_fscan_array(in, arr_a4_size);
  /* NULL pointer and successfull scanning check */
  arr = jagged4_new(arr_a0, arr_a1, arr_a2, arr_a3, arr_a4);
  /* NULL pointer check */
  return arr;
}

void jagged4_free(jagged4 * arr)
{
  free(arr->a4);
  free(arr->a3);
  free(arr->a2);
  free(arr->a1);
  free(arr);
}

// #include "jagged.h"
//
// /****************************** jagged1_fprint ********************************/
// static void array1_fprint(FILE *out, int **a1, int a0)
// {
//   int i;
//
//   fputc('{', out);
//   for (i = 0; i < a0 - 1; ++i)
//   {
//     fprintf(out, "%d", **a1);
//     ++*a1;
//     fputc(',', out);
//   }
//   if (a0)
//   {
//     fprintf(out, "%d", **a1);
//     ++*a1;
//   }
//   fputc('}', out);
// }
//
// void jagged1_fprint(FILE *out, const jagged1 *arr)
// {
//   int arr_a0;
//   int *arr_a1;
//
//   arr_a0 = arr->a0;
//   arr_a1 = arr->a1;
//   array1_fprint(out, &arr_a1, arr_a0);
// }
//
// /****************************** jagged2_fprint ********************************/
// static void array2_fprint(FILE *out, int **a2, int **a1, int a0)
// {
//   int i;
//
//   fputc('{', out);
//   for (i = 0; i < a0 - 1; ++i)
//   {
//     array1_fprint(out, a2, **a1);
//     ++*a1;
//     fputc(',', out);
//   }
//   if (a0)
//   {
//     array1_fprint(out, a2, **a1);
//     ++*a1;
//   }
//   fputc('}', out);
// }
//
// void jagged2_fprint(FILE *out, const jagged2 *arr)
// {
//   int arr_a0;
//   int *arr_a1, *arr_a2;
//
//   arr_a0 = arr->a0;
//   arr_a1 = arr->a1;
//   arr_a1 = arr->a2;
//   array2_fprint(out, &arr_a2, &arr_a1, arr_a0);
// }
//
// /****************************** jagged3_fprint ********************************/
// static void array3_fprint(FILE *out, int **a3, int **a2, int **a1, int a0)
// {
//   int i;
//
//   fputc('{', out);
//   for (i = 0; i < a0 - 1; ++i)
//   {
//     array2_fprint(out, a3, a2, **a1);
//     ++*a1;
//     fputc(',', out);
//   }
//   if (a0)
//   {
//     array2_fprint(out, a3, a2, **a1);
//     ++*a1;
//   }
//   fputc('}', out);
// }
//
// void jagged3_fprint(FILE *out, const jagged3 *arr)
// {
//   int arr_a0;
//   int *arr_a1, *arr_a2, *arr_a3;
//
//   arr_a0 = arr->a0;
//   arr_a1 = arr->a1;
//   arr_a1 = arr->a2;
//   arr_a3 = arr->a3;
//   array3_fprint(out, &arr_a3, &arr_a2, &arr_a1, arr_a0);
// }
//
// /****************************** jagged4_fprint ********************************/
// static void array4_fprint(
//   FILE *out, int **a4, int **a3, int **a2, int **a1, int a0)
// {
//   int i;
//
//   fputc('{', out);
//   for (i = 0; i < a0 - 1; ++i)
//   {
//     array3_fprint(out, a4, a3, a2, **a1);
//     ++*a1;
//     fputc(',', out);
//   }
//   if (a0)
//   {
//     array3_fprint(out, a4, a3, a2, **a1);
//     ++*a1;
//   }
//   fputc('}', out);
// }
//
// void jagged4_fprint(FILE *out, const jagged4 *arr)
// {
//   int arr_a0;
//   int *arr_a1, *arr_a2, *arr_a3, *arr_a4;
//
//   arr_a0 = arr->a0;
//   arr_a1 = arr->a1;
//   arr_a1 = arr->a2;
//   arr_a3 = arr->a3;
//   arr_a4 = arr->a4;
//   array4_fprint(out, &arr_a4, &arr_a3, &arr_a2, &arr_a1, arr_a0);
// }
