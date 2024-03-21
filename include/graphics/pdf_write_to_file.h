#include "drawer.h"
#include "get_index_t.h"
#include "get_total_steps_t.h"

void pdf_write_to_file(
  const char * filename,
  double width,
  double height,
  void * a,
  drawer draw,
  get_index_t get_index,
  get_total_steps_t total_steps);
