#ifndef JAGGED_H
#define JAGGED_H

#include <stdio.h>

/********************************** jagged1 ***********************************/
typedef struct jagged1
{
  int a0;
  int * a1;
} jagged1;

void jagged1_free(jagged1 * arr);
jagged1 * jagged1_fscan(FILE * in, const char * format);
void jagged1_fprint(FILE * out, const jagged1 * arr, const char * format);

int jagged1_part1(const jagged1 * arr, int i1);

int jagged1_total_sum(const jagged1 * arr);

jagged1 * jagged1_complement(int n, const jagged1 * a);

jagged1 * jagged1_delete_duplicates(jagged1 * arr);

int jagged1_member(const jagged1 * arr, int element);

int jagged1_intersection_count(const jagged1 * arr, const jagged1 * arr2);

int jagged1_intersection_unique(const jagged1 * arr1, const jagged1 * arr2);

void jagged1_intersection(
  jagged1 * res, const jagged1 * arr1, const jagged1 * arr2);

int jagged1_position(const jagged1 * arr, int element);

int jagged1_signature(const jagged1 * arr);

int jagged1_complement_simplicial(const jagged1 * cell_nodes,
                                  const jagged1 * hyperface_nodes);

void jagged1_delete(jagged1 * result, const jagged1 * arr, int element);

int jagged1_relative_sign(const jagged1 * cell_nodes,
                          const jagged1 * hyperface_nodes);

/********************************** jagged2 ***********************************/
typedef struct jagged2
{
  int a0;
  int * a1;
  int * a2;
} jagged2;

void jagged2_free(jagged2 * arr);
jagged2 * jagged2_fscan(FILE * in, const char * format);
void jagged2_fprint(FILE * out, const jagged2 * arr, const char * format);

void jagged2_part1(jagged1 * res, const jagged2 * arr, int i1);
int jagged2_part2(const jagged2 * arr, int i1, int i2);


/********************************** jagged3 ***********************************/
typedef struct jagged3
{
  int a0;
  int * a1;
  int * a2;
  int * a3;
} jagged3;

void jagged3_free(jagged3 * arr);
jagged3 * jagged3_fscan(FILE * in, const char * format);
void jagged3_fprint(FILE * out, const jagged3 * arr, const char * format);

void jagged3_part1(jagged2 * res, const jagged3 * arr, int i1);
void jagged3_part2(jagged1 * res, const jagged3 * arr, int i1, int i2);
int jagged3_part3(const jagged3 * arr, int i1, int i2, int i3);

/********************************** jagged4 ***********************************/
typedef struct jagged4
{
  int a0;
  int * a1;
  int * a2;
  int * a3;
  int * a4;
} jagged4;

void jagged4_free(jagged4 * arr);
jagged4 * jagged4_fscan(FILE * in, const char * format);
void jagged4_fprint(FILE * out, const jagged4 * arr, const char * format);

void jagged4_part1(jagged3 * res, const jagged4 * arr, int i1);
void jagged4_part2(jagged2 * res, const jagged4 * arr, int i1, int i2);
void jagged4_part3(jagged1 * res, const jagged4 * arr, int i1, int i2, int i3);
int jagged4_part4(const jagged4 * arr, int i1, int i2, int i3, int i4);

#endif /* JAGGED_H */
