/*
This file contains signatures of functions acting on matrices of type double.
They are represented in a column-major form by a flattened array of doubles.
*/

#include <stdio.h>

/* Print $d * $n matrix $a to $out. */
void matrix_file_print(FILE * out, int d, int n, const double * a);

/*
Determinant of a square matrix $a of dimension $d$.
For now, only of dimensions up to 3 are implemented.
*/
double matrix_determinant(int d, const double * a);

/*
Let $a be a $d * $n matrix, $b := $a $a^T is a $d * $d matrix.
Memory for $b is allocated by the caller who must also fill it with zeros.
*/
void matrix_times_transpose(double * b, int d, int n, const double * a);

/*
Let $a be a $d * $d matrix, $b := $a^{-1}.
Memory for $b is allocated by the caller.
*/
void matrix_inverse(double * b, int d, const double * a);

/*
Let $a be an $n * $d matrix.
Let $x be a $d vector.
We calculate the $n vector $b = product($a, $x).
$b is initially set to zero.
*/
void matrix_times_vector(
  double * b, int n, int d, const double * a, const double * x);

/*
Let $d be dimension, $n >= d.
Let $a be $d * $n matrix with linearly independent columns.
Let $tmp = product($a, transpose($a)).
Then $tmp is $d * $d symmetric positive definite matrix.
Let $tmp1 = inverse($tmp).
Then $tmp1 is also $d * $d symmetric positive definite matrix.
Let $b = product(transpose($a), $tmp1).
Then $b is an $n * $d matrix, the Moore-Penrose inverse of $a.

$b has to be allocated as a zero array.
For applications, usually $d <= 3.
Hence, stack arrays of length 9 are enough for $tmp and $tmp1.
*/
void matrix_moore_penrose_inverse(double * b, int d, int n, const double * a);
