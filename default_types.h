
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


#ifndef DEFAULT_TTYPES
#define DEFAULT_TTYPES(macro, type) \
    macro(type, char) \
    macro(type, signed_char) \
    macro(type, uchar) \
    macro(type, short) \
    macro(type, ushort) \
    macro(type, int) \
    macro(type, uint) \
    macro(type, long) \
    macro(type, ulong) \
    macro(type, long_long) \
    macro(type, ulong_long) \
    macro(type, float) \
    macro(type, double) \
    macro(type, long_double) \
    macro(type, type) \
    macro(char, type) \
    macro(signed_char, type) \
    macro(uchar, type) \
    macro(short, type) \
    macro(ushort, type) \
    macro(int, type) \
    macro(uint, type) \
    macro(long, type) \
    macro(ulong, type) \
    macro(long_long, type) \
    macro(ulong_long, type) \
    macro(float, type) \
    macro(double, type) \
    macro(long_double, type)
#endif


#ifndef DEFAULT_FOR_TTYPES
#define DEFAULT_FOR_TTYPES(macro) \
    DEFAULT_TTYPES(macro, char) \
    DEFAULT_TTYPES(macro, signed_char) \
    DEFAULT_TTYPES(macro, uchar) \
    DEFAULT_TTYPES(macro, short) \
    DEFAULT_TTYPES(macro, ushort) \
    DEFAULT_TTYPES(macro, int) \
    DEFAULT_TTYPES(macro, uint) \
    DEFAULT_TTYPES(macro, long) \
    DEFAULT_TTYPES(macro, ulong) \
    DEFAULT_TTYPES(macro, long_long) \
    DEFAULT_TTYPES(macro, ulong_long) \
    DEFAULT_TTYPES(macro, float) \
    DEFAULT_TTYPES(macro, double) \
    DEFAULT_TTYPES(macro, long_double)
#endif

#ifndef DEFAULT_TTTYPES
#define DEFAULT_TTTYPES(macro, type, epyt) \
    macro(epyt, type, char) \
    macro(epyt, type, signed_char) \
    macro(epyt, type, uchar) \
    macro(epyt, type, short) \
    macro(epyt, type, ushort) \
    macro(epyt, type, int) \
    macro(epyt, type, uint) \
    macro(epyt, type, long) \
    macro(epyt, type, ulong) \
    macro(epyt, type, long_long) \
    macro(epyt, type, ulong_long) \
    macro(epyt, type, float) \
    macro(epyt, type, double) \
    macro(epyt, type, long_double) \
    macro(epyt, type, type) \
    macro(epyt, char, type) \
    macro(epyt, signed_char, type) \
    macro(epyt, uchar, type) \
    macro(epyt, short, type) \
    macro(epyt, ushort, type) \
    macro(epyt, int, type) \
    macro(epyt, uint, type) \
    macro(epyt, long, type) \
    macro(epyt, ulong, type) \
    macro(epyt, long_long, type) \
    macro(epyt, ulong_long, type) \
    macro(epyt, float, type) \
    macro(epyt, double, type) \
    macro(epyt, long_double, type) \
    macro(char, epyt, type) \
    macro(signed_char, epyt, type) \
    macro(uchar, epyt, type) \
    macro(short, epyt, type) \
    macro(ushort, epyt, type) \
    macro(int, epyt, type) \
    macro(uint, epyt, type) \
    macro(long, epyt, type) \
    macro(ulong, epyt, type) \
    macro(long_long, epyt, type) \
    macro(ulong_long, epyt, type) \
    macro(float, epyt, type) \
    macro(double, epyt, type) \
    macro(long_double, epyt, type) 
#endif


#ifndef DEFAULT_FOR_TTTYPES
#define DEFAULT_FOR_TTTYPES(macro) \
    DEFAULT_TTTYPES(macro, char, char) \
    DEFAULT_TTTYPES(macro, signed_char, signed_char) \
    DEFAULT_TTTYPES(macro, uchar, uchar) \
    DEFAULT_TTTYPES(macro, short, short) \
    DEFAULT_TTTYPES(macro, ushort, ushort) \
    DEFAULT_TTTYPES(macro, int, int) \
    DEFAULT_TTTYPES(macro, uint, uint) \
    DEFAULT_TTTYPES(macro, long, long) \
    DEFAULT_TTTYPES(macro, ulong, ulong) \
    DEFAULT_TTTYPES(macro, long_long, long_long) \
    DEFAULT_TTTYPES(macro, ulong_long, ulong_long) \
    DEFAULT_TTTYPES(macro, float, float) \
    DEFAULT_TTTYPES(macro, double, double) \
    DEFAULT_TTTYPES(macro, long_double, long_double) \
#endif
