#include "idec_animation_intrinsic_functions.h"
#include "idec_filled_window.h"

static double get_width(const void * animation)
{
  return ((struct idec_filled_window *) animation)->width;
}

static double get_height(const void * animation)
{
  return ((struct idec_filled_window *) animation)->height;
}

static int get_total_steps(const void * animation)
{
  return ((struct idec_filled_window *) animation)->total_colors;
}

static int * get_old_index_address(const void * animation)
{
  return &(((struct idec_filled_window *) animation)->old_index);
}

static int * get_new_index_address(const void * animation)
{
  return &(((struct idec_filled_window *) animation)->new_index);
}

static void update_new_index(void * animation)
{
  ((struct idec_filled_window *) animation)->new_index += 1;
}

static const struct idec_animation_intrinsic_functions
intrinsic_functions =
{
  get_width,
  get_height,
  get_total_steps,
  get_old_index_address,
  get_new_index_address,
  update_new_index
};

const struct idec_animation_intrinsic_functions *
idec_filled_window_intrinsic_functions = &intrinsic_functions;
