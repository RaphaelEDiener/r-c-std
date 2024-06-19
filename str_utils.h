#include <stdio.h>
#include "default_types.h"

#ifndef STRING_UTILS
#define STRING_UTILS

/**
 * moves fp to next non whitespace char
 */
void skip_whitespace(FILE* fp);

int peak(FILE* fp);

uchar is_digit  (char c);
uchar is_lower  (char c);
uchar is_upper  (char c);
uchar is_alpha  (char c);
uchar is_control(char c);

#endif
