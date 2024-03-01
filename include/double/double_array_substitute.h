#ifndef _double_array_substitute_h_
#define _double_array_substitute_h_

/* Sets b := {a[position[0]], ..., a[position[n - 1]]}. */
void double_array_substitute(
  double * b,
  int n,
  const double * a,
  const int * position);

#endif /* _double_array_substitute_h_ */
