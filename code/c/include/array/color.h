#ifndef _color_h
#define _color_h

#define color_red "\x1B[31m"
#define color_green "\x1B[32m"
#define color_blue "\x1B[34m"
#define color_none "\x1B[m"
#define color_error_position(file, line)\
fprintf(stderr, "%s%s:%d:%s ", color_blue, file, line, color_none)

#endif /* _color_h */
