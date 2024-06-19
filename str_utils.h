#include <stdio.h>

#ifndef STRING_UTILS
#define STRING_UTILS

/**
 * moves fp to next non whitespace char
 */
void skip_whitespace(FILE* fp);

int peak(FILE* fp);

unsigned char is_digit  (char c);
unsigned char is_lower  (char c);
unsigned char is_upper  (char c);
unsigned char is_alpha  (char c); // todo: test
unsigned char is_control(char c); // todo: test

#endif
