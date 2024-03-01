#ifndef _double_array_substitute_inverse_h_
#define _double_array_substitute_inverse_h_

/* Sets b[position[0]] := a[0], ..., b[position[n - 1]] := a[n - 1] . */
double double_array_substitute_inverse(
  double * b,
  int n,
  const double * a,
  const int * position);

#endif /* _double_array_substitute_inverse_h_ */
