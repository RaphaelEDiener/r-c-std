#include <stdio.h>
#include "default_types.h"
#include "dynamic_array.h"

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

typedef charDa String;
DEFINE_RESULT(String);
DEFINE_SWAP(String);
DEFINE_DA(String);

String      join_Da   (StringDa        );
String      join_with (StringDa, String);
String      join_uchar(StringDa, uchar );
String      join_schar(StringDa, schar );
StringRes   load_file (const char* name);
StringDaRes split_file(const char* name);
StringDaRes split      (String        );
StringDaRes split_at   (String, String);
StringDaRes split_uchar(String, uchar );
StringDaRes split_schar(String, schar );

#endif
