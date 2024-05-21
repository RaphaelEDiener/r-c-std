
#ifndef TYPE_CONCATS
#define TYPE_CONCATS
typedef signed char signed_char;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long long_long;
typedef unsigned long long ulong_long;
typedef long double long_double;
#endif

#ifndef DEFAULT_TYPES
#define DEFAULT_TYPES(macro) \
    macro(char) \
    macro(signed_char) \
    macro(uchar) \
    macro(short) \
    macro(ushort) \
    macro(int) \
    macro(uint) \
    macro(long) \
    macro(ulong) \
    macro(long_long) \
    macro(ulong_long) \
    macro(float) \
    macro(double) \
    macro(long_double)
#endif


