#ifndef IMATH_H
#define IMATH_H

void imath_swap(int * a, int * b);

int imath_pow(int a, int b);

void imath_cartesian_product_next(int * a, int d, const int * n);

int imath_binom(int a, int b);
void imath_combination_next(int * a, int m, int n);
int imath_combination_index(int * comb, int m, int n);

int imath_factorial(int n);

#endif /* IMATH_H */
