#ifndef JAGGED_PRIVATE_H
#define JAGGED_PRIVATE_H

#include "jagged.h"

/******************************************************************************/
/*                                  jagged1                                   */
/******************************************************************************/

/******************************* jagged1_file_scan ********************************/
jagged1 * jagged1_file_scan_raw(FILE * in);

#define JAGGED1_file_scan_format_total 1

static const char * jagged1_file_scan_format[JAGGED1_file_scan_format_total] =
  {
    "--raw"
  };

typedef jagged1 * (*jagged1_file_scan_function_type)(FILE *);

static const jagged1_file_scan_function_type
jagged1_file_scan_function[JAGGED1_file_scan_format_total] =
  {
    jagged1_file_scan_raw
  };

/******************************* jagged1_file_print *******************************/
void jagged1_file_print_raw(FILE * out, const jagged1 * arr);
void jagged1_file_print_curly(FILE * out, const jagged1 * arr);

#define JAGGED1_file_print_format_total 2

static const char * jagged1_file_print_format[JAGGED1_file_print_format_total] =
  {
    "--raw",
    "--curly"
  };

typedef void (*jagged1_file_print_function_type)(FILE *, const jagged1 *);

static const jagged1_file_print_function_type
jagged1_file_print_function[JAGGED1_file_print_format_total] =
  {
    jagged1_file_print_raw,
    jagged1_file_print_curly
  };

/******************************************************************************/
/*                                  jagged2                                   */
/******************************************************************************/

/******************************* jagged2_file_scan ********************************/
jagged2 * jagged2_file_scan_raw(FILE * in);

#define JAGGED2_file_scan_format_total 1

static const char * jagged2_file_scan_format[JAGGED2_file_scan_format_total] =
  {
    "--raw"
  };

typedef jagged2 * (*jagged2_file_scan_function_type)(FILE *);

static const jagged2_file_scan_function_type
jagged2_file_scan_function[JAGGED2_file_scan_format_total] =
  {
    jagged2_file_scan_raw
  };

/******************************* jagged2_file_print *******************************/
void jagged2_file_print_raw(FILE * out, const jagged2 * arr);
void jagged2_file_print_curly(FILE * out, const jagged2 * arr);

#define JAGGED2_file_print_format_total 2

static const char * jagged2_file_print_format[JAGGED2_file_print_format_total] =
  {
    "--raw",
    "--curly"
  };

typedef void (*jagged2_file_print_function_type)(FILE *, const jagged2 *);

static const jagged2_file_print_function_type
jagged2_file_print_function[JAGGED2_file_print_format_total] =
  {
    jagged2_file_print_raw,
    jagged2_file_print_curly
  };

/******************************************************************************/
/*                                  jagged3                                   */
/******************************************************************************/

/******************************* jagged3_file_scan ********************************/
jagged3 * jagged3_file_scan_raw(FILE * in);

#define JAGGED3_file_scan_format_total 1

static const char * jagged3_file_scan_format[JAGGED3_file_scan_format_total] =
  {
    "--raw"
  };

typedef jagged3 * (*jagged3_file_scan_function_type)(FILE *);

static const jagged3_file_scan_function_type
jagged3_file_scan_function[JAGGED3_file_scan_format_total] =
  {
    jagged3_file_scan_raw
  };

/******************************* jagged3_file_print *******************************/
void jagged3_file_print_raw(FILE * out, const jagged3 * arr);
void jagged3_file_print_curly(FILE * out, const jagged3 * arr);

#define JAGGED3_file_print_format_total 2

static const char * jagged3_file_print_format[JAGGED3_file_print_format_total] =
  {
    "--raw",
    "--curly"
  };

typedef void (*jagged3_file_print_function_type)(FILE *, const jagged3 *);

static const jagged3_file_print_function_type
jagged3_file_print_function[JAGGED3_file_print_format_total] =
  {
    jagged3_file_print_raw,
    jagged3_file_print_curly
  };

/******************************************************************************/
/*                                  jagged4                                   */
/******************************************************************************/

/******************************* jagged4_file_scan ********************************/
jagged4 * jagged4_file_scan_raw(FILE * in);

#define JAGGED4_file_scan_format_total 1

static const char * jagged4_file_scan_format[JAGGED4_file_scan_format_total] =
  {
    "--raw"
  };

typedef jagged4 * (*jagged4_file_scan_function_type)(FILE *);

static const jagged4_file_scan_function_type
jagged4_file_scan_function[JAGGED4_file_scan_format_total] =
  {
    jagged4_file_scan_raw
  };

/******************************* jagged4_file_print *******************************/
void jagged4_file_print_raw(FILE * out, const jagged4 * arr);
void jagged4_file_print_curly(FILE * out, const jagged4 * arr);

#define JAGGED4_file_print_format_total 2

static const char * jagged4_file_print_format[JAGGED4_file_print_format_total] =
  {
    "--raw",
    "--curly"
  };

typedef void (*jagged4_file_print_function_type)(FILE *, const jagged4 *);

static const jagged4_file_print_function_type
jagged4_file_print_function[JAGGED4_file_print_format_total] =
  {
    jagged4_file_print_raw,
    jagged4_file_print_curly
  };

#endif
