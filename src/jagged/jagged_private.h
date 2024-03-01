#ifndef JAGGED_PRIVATE_H
#define JAGGED_PRIVATE_H

#include "jagged.h"

/******************************************************************************/
/*                                  jagged1                                   */
/******************************************************************************/

/******************************* jagged1_fscan ********************************/
jagged1 * jagged1_fscan_raw(FILE * in);

#define JAGGED1_FSCAN_FORMAT_TOTAL 1

static const char * jagged1_fscan_format[JAGGED1_FSCAN_FORMAT_TOTAL] =
  {
    "--raw"
  };

typedef jagged1 * (*jagged1_fscan_function_type)(FILE *);

static const jagged1_fscan_function_type
jagged1_fscan_function[JAGGED1_FSCAN_FORMAT_TOTAL] =
  {
    jagged1_fscan_raw
  };

/******************************* jagged1_fprint *******************************/
void jagged1_fprint_raw(FILE * out, const jagged1 * arr);
void jagged1_fprint_curly(FILE * out, const jagged1 * arr);

#define JAGGED1_FPRINT_FORMAT_TOTAL 2

static const char * jagged1_fprint_format[JAGGED1_FPRINT_FORMAT_TOTAL] =
  {
    "--raw",
    "--curly"
  };

typedef void (*jagged1_fprint_function_type)(FILE *, const jagged1 *);

static const jagged1_fprint_function_type
jagged1_fprint_function[JAGGED1_FPRINT_FORMAT_TOTAL] =
  {
    jagged1_fprint_raw,
    jagged1_fprint_curly
  };

/******************************************************************************/
/*                                  jagged2                                   */
/******************************************************************************/

/******************************* jagged2_fscan ********************************/
jagged2 * jagged2_fscan_raw(FILE * in);

#define JAGGED2_FSCAN_FORMAT_TOTAL 1

static const char * jagged2_fscan_format[JAGGED2_FSCAN_FORMAT_TOTAL] =
  {
    "--raw"
  };

typedef jagged2 * (*jagged2_fscan_function_type)(FILE *);

static const jagged2_fscan_function_type
jagged2_fscan_function[JAGGED2_FSCAN_FORMAT_TOTAL] =
  {
    jagged2_fscan_raw
  };

/******************************* jagged2_fprint *******************************/
void jagged2_fprint_raw(FILE * out, const jagged2 * arr);
void jagged2_fprint_curly(FILE * out, const jagged2 * arr);

#define JAGGED2_FPRINT_FORMAT_TOTAL 2

static const char * jagged2_fprint_format[JAGGED2_FPRINT_FORMAT_TOTAL] =
  {
    "--raw",
    "--curly"
  };

typedef void (*jagged2_fprint_function_type)(FILE *, const jagged2 *);

static const jagged2_fprint_function_type
jagged2_fprint_function[JAGGED2_FPRINT_FORMAT_TOTAL] =
  {
    jagged2_fprint_raw,
    jagged2_fprint_curly
  };

/******************************************************************************/
/*                                  jagged3                                   */
/******************************************************************************/

/******************************* jagged3_fscan ********************************/
jagged3 * jagged3_fscan_raw(FILE * in);

#define JAGGED3_FSCAN_FORMAT_TOTAL 1

static const char * jagged3_fscan_format[JAGGED3_FSCAN_FORMAT_TOTAL] =
  {
    "--raw"
  };

typedef jagged3 * (*jagged3_fscan_function_type)(FILE *);

static const jagged3_fscan_function_type
jagged3_fscan_function[JAGGED3_FSCAN_FORMAT_TOTAL] =
  {
    jagged3_fscan_raw
  };

/******************************* jagged3_fprint *******************************/
void jagged3_fprint_raw(FILE * out, const jagged3 * arr);
void jagged3_fprint_curly(FILE * out, const jagged3 * arr);

#define JAGGED3_FPRINT_FORMAT_TOTAL 2

static const char * jagged3_fprint_format[JAGGED3_FPRINT_FORMAT_TOTAL] =
  {
    "--raw",
    "--curly"
  };

typedef void (*jagged3_fprint_function_type)(FILE *, const jagged3 *);

static const jagged3_fprint_function_type
jagged3_fprint_function[JAGGED3_FPRINT_FORMAT_TOTAL] =
  {
    jagged3_fprint_raw,
    jagged3_fprint_curly
  };

/******************************************************************************/
/*                                  jagged4                                   */
/******************************************************************************/

/******************************* jagged4_fscan ********************************/
jagged4 * jagged4_fscan_raw(FILE * in);

#define JAGGED4_FSCAN_FORMAT_TOTAL 1

static const char * jagged4_fscan_format[JAGGED4_FSCAN_FORMAT_TOTAL] =
  {
    "--raw"
  };

typedef jagged4 * (*jagged4_fscan_function_type)(FILE *);

static const jagged4_fscan_function_type
jagged4_fscan_function[JAGGED4_FSCAN_FORMAT_TOTAL] =
  {
    jagged4_fscan_raw
  };

/******************************* jagged4_fprint *******************************/
void jagged4_fprint_raw(FILE * out, const jagged4 * arr);
void jagged4_fprint_curly(FILE * out, const jagged4 * arr);

#define JAGGED4_FPRINT_FORMAT_TOTAL 2

static const char * jagged4_fprint_format[JAGGED4_FPRINT_FORMAT_TOTAL] =
  {
    "--raw",
    "--curly"
  };

typedef void (*jagged4_fprint_function_type)(FILE *, const jagged4 *);

static const jagged4_fprint_function_type
jagged4_fprint_function[JAGGED4_FPRINT_FORMAT_TOTAL] =
  {
    jagged4_fprint_raw,
    jagged4_fprint_curly
  };

#endif
