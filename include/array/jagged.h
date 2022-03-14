#ifndef JAGGED_H
#define JAGGED_H

#include <stdio.h>

/********************************** jagged1 ***********************************/
typedef struct jagged1
{
  int a0;
  int * a1;
} jagged1;

void jagged1_set(jagged1 * arr, int arr_a0, int * arr_a1);

jagged1 * jagged1_new(int arr_a0, int * arr_a1);

int jagged1_part1(const jagged1 * arr, int i1);

void jagged1_fprint(FILE * out, const jagged1 * arr);
                  
void jagged1_print(const jagged1 * arr);

void jagged1_fprint_annotated(
  FILE * out, const jagged1 * arr, const char * name);

void jagged1_fprint_raw(FILE * out, const jagged1 * arr);

jagged1 * jagged1_fscan_raw(FILE * in);

void jagged1_free(jagged1 * arr);

jagged1 * jagged1_complement(int n, const jagged1 * a);

/********************************** jagged2 ***********************************/
typedef struct jagged2
{
  int a0;
  int * a1;
  int * a2;
} jagged2;

void jagged2_set(jagged2 * arr, int arr_a0, int * arr_a1, int * arr_a2);

jagged2 * jagged2_new(int arr_a0, int * arr_a1, int * arr_a2);

void jagged2_part1(jagged1 * res, const jagged2 * arr, int i1);

int jagged2_part2(const jagged2 * arr, int i1, int i2);

void jagged2_fprint(FILE * out, const jagged2 * arr);

void jagged2_print(const jagged2 * arr);

void jagged2_fprint_annotated(
  FILE * out, const jagged2 * arr, const char * name);

void jagged2_fprint_raw(FILE * out, const jagged2 * arr);

jagged2 * jagged2_fscan_raw(FILE * in);

void jagged2_free(jagged2 * arr);

/********************************** jagged3 ***********************************/
typedef struct jagged3
{
  int a0;
  int * a1;
  int * a2;
  int * a3;
} jagged3;

void jagged3_set(jagged3 * arr, int arr_a0, int * arr_a1, int * arr_a2,
                 int * arr_a3);

jagged3 * jagged3_new(int arr_a0, int * arr_a1, int * arr_a2, int * arr_a3);

void jagged3_part1(jagged2 * res, const jagged3 * arr, int i1);

void jagged3_part2(jagged1 * res, const jagged3 * arr, int i1, int i2);

int jagged3_part3(const jagged3 * arr, int i1, int i2, int i3);

void jagged3_fprint(FILE * out, const jagged3 * arr);

void jagged3_print(const jagged3 * arr);

void jagged3_fprint_annotated(
  FILE * out, const jagged3 * arr, const char * name);

void jagged3_fprint_raw(FILE * out, const jagged3 * arr);

jagged3 * jagged3_fscan_raw(FILE * in);

void jagged3_free(jagged3 * arr);

/********************************** jagged4 ***********************************/
typedef struct jagged4
{
  int a0;
  int * a1;
  int * a2;
  int * a3;
  int * a4;
} jagged4;

void jagged4_set(jagged4 * arr, int arr_a0, int * arr_a1, int * arr_a2,
                 int * arr_a3, int * arr_a4);
        
jagged4 * jagged4_new(int arr_a0, int * arr_a1, int * arr_a2, int * arr_a3,
                      int * arr_a4);

void jagged4_part1(jagged3 * res, const jagged4 * arr, int i1);

void jagged4_part2(jagged2 * res, const jagged4 * arr, int i1, int i2);

void jagged4_part3(jagged1 * res, const jagged4 * arr, int i1, int i2, int i3);

int jagged4_part4(const jagged4 * arr, int i1, int i2, int i3, int i4);

void jagged4_fprint(FILE * out, const jagged4 * arr);

void jagged4_print(const jagged4 * arr);

void jagged4_fprint_annotated(
  FILE * out, const jagged4 * arr, const char * name);

void jagged4_fprint_raw(FILE * out, const jagged4 * arr);

jagged4 * jagged4_fscan_raw(FILE * in);
    
void jagged4_free(jagged4 * arr);

#endif /* JAGGED_H */
