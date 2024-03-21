#include "gtk_time_handler.h"

int gtk_time_handler(GtkWidget * widget)
{
  gtk_widget_queue_draw(widget);
  return TRUE;
}
