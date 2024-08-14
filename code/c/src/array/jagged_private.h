#ifndef _jagged_private_h
#define _jagged_private_h

#include "jagged.h"

/******************************************************************************/
/*                                  jagged1                                   */
/******************************************************************************/

/******************************* jagged1_file_scan ********************************/
jagged1 * jagged1_file_scan_raw(FILE * in);

/******************************* jagged1_file_print *******************************/
void jagged1_file_print_raw(FILE * out, const jagged1 * arr);
void jagged1_file_print_curly(FILE * out, const jagged1 * arr);

/******************************************************************************/
/*                                  jagged2                                   */
/******************************************************************************/

/******************************* jagged2_file_scan ********************************/
jagged2 * jagged2_file_scan_raw(FILE * in);

/******************************* jagged2_file_print *******************************/
void jagged2_file_print_raw(FILE * out, const jagged2 * arr);
void jagged2_file_print_curly(FILE * out, const jagged2 * arr);

/******************************************************************************/
/*                                  jagged3                                   */
/******************************************************************************/

/******************************* jagged3_file_scan ********************************/
jagged3 * jagged3_file_scan_raw(FILE * in);

/******************************* jagged3_file_print *******************************/
void jagged3_file_print_raw(FILE * out, const jagged3 * arr);
void jagged3_file_print_curly(FILE * out, const jagged3 * arr);

/******************************************************************************/
/*                                  jagged4                                   */
/******************************************************************************/

/******************************* jagged4_file_scan ********************************/
jagged4 * jagged4_file_scan_raw(FILE * in);

/******************************* jagged4_file_print *******************************/
void jagged4_file_print_raw(FILE * out, const jagged4 * arr);
void jagged4_file_print_curly(FILE * out, const jagged4 * arr);

#endif /* _jagged_private_h */
