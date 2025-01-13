#ifndef _color_h
#define _color_h

#define color_red "\x1B[31m"
#define color_green "\x1B[32m"
#define color_yellow "\x1B[33m"
#define color_blue "\x1B[34m"
#define color_magenta "\x1B[35m"
#define color_cyan "\x1B[36m"
#define color_bright_cyan "\x1B[96m"
#define color_none "\x1B[m"

#define color_variable color_green
#define color_stdlib color_magenta

#define color_error_position(file, line)\
fprintf(stderr, "%s%s%s:%s%d%s: %serror%s: ",\
  color_bright_cyan, file, color_none,\
  color_yellow, line, color_none,\
  color_red, color_none)

#endif /* _color_h */
