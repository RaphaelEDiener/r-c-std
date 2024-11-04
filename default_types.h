#include <stddef.h>

#ifndef TYPE_CONCATS
#define TYPE_CONCATS
typedef signed   char      schar;
typedef unsigned char      uchar;
typedef unsigned short     ushort;
typedef unsigned int       uint;
typedef unsigned long      ulong;
typedef long     long      llong;
typedef unsigned long long ullong;
typedef long     double    ldouble;
#endif

#ifndef DEFAULT_TYPES
#define DEFAULT_TYPES(macro) \
    macro(char) \
    macro(schar) \
    macro(uchar) \
    macro(short) \
    macro(ushort) \
    macro(int) \
    macro(uint) \
    macro(long) \
    macro(ulong) \
    macro(llong) \
    macro(ullong) \
    macro(float) \
    macro(double) \
    macro(ldouble) \
    macro(size_t)
#endif


#ifndef DEFAULT_TTYPES
#define DEFAULT_TTYPES(macro, type) \
    macro(type, char) \
    macro(type, schar) \
    macro(type, uchar) \
    macro(type, short) \
    macro(type, ushort) \
    macro(type, int) \
    macro(type, uint) \
    macro(type, long) \
    macro(type, ulong) \
    macro(type, llong) \
    macro(type, ullong) \
    macro(type, float) \
    macro(type, double) \
    macro(type, ldouble) \
    macro(type, size_t)
#endif


#ifndef DEFAULT_FOR_TTYPES
#define DEFAULT_FOR_TTYPES(macro) \
    DEFAULT_TTYPES(macro, char) \
    DEFAULT_TTYPES(macro, schar) \
    DEFAULT_TTYPES(macro, uchar) \
    DEFAULT_TTYPES(macro, short) \
    DEFAULT_TTYPES(macro, ushort) \
    DEFAULT_TTYPES(macro, int) \
    DEFAULT_TTYPES(macro, uint) \
    DEFAULT_TTYPES(macro, long) \
    DEFAULT_TTYPES(macro, ulong) \
    DEFAULT_TTYPES(macro, llong) \
    DEFAULT_TTYPES(macro, ullong) \
    DEFAULT_TTYPES(macro, float) \
    DEFAULT_TTYPES(macro, double) \
    DEFAULT_TTYPES(macro, ldouble) \
    DEFAULT_TTYPES(macro, size_t)
#endif

#ifndef DEFAULT_TTTYPES
#define DEFAULT_TTTYPES(macro, type, epyt) \
    macro(epyt, type, char) \
    macro(epyt, type, schar) \
    macro(epyt, type, uchar) \
    macro(epyt, type, short) \
    macro(epyt, type, ushort) \
    macro(epyt, type, int) \
    macro(epyt, type, uint) \
    macro(epyt, type, long) \
    macro(epyt, type, ulong) \
    macro(epyt, type, llong) \
    macro(epyt, type, ullong) \
    macro(epyt, type, float) \
    macro(epyt, type, double) \
    macro(epyt, type, ldouble) \
    macro(epyt, type, size_t) \
    macro(epyt, type, type) \
    macro(epyt, char, type) \
    macro(epyt, schar, type) \
    macro(epyt, uchar, type) \
    macro(epyt, short, type) \
    macro(epyt, ushort, type) \
    macro(epyt, int, type) \
    macro(epyt, uint, type) \
    macro(epyt, long, type) \
    macro(epyt, ulong, type) \
    macro(epyt, llong, type) \
    macro(epyt, ullong, type) \
    macro(epyt, float, type) \
    macro(epyt, double, type) \
    macro(epyt, ldouble, type) \
    macro(epyt, size_t, type) \
    macro(char, epyt, type) \
    macro(schar, epyt, type) \
    macro(uchar, epyt, type) \
    macro(short, epyt, type) \
    macro(ushort, epyt, type) \
    macro(int, epyt, type) \
    macro(uint, epyt, type) \
    macro(long, epyt, type) \
    macro(ulong, epyt, type) \
    macro(llong, epyt, type) \
    macro(ullong, epyt, type) \
    macro(float, epyt, type) \
    macro(double, epyt, type) \
    macro(ldouble, epyt, type) \
    macro(size_t, epyt, type) 
#endif


#ifndef DEFAULT_FOR_TTTYPES
#define DEFAULT_FOR_TTTYPES(macro) \
    DEFAULT_TTTYPES(macro, char, char) \
    DEFAULT_TTTYPES(macro, schar, schar) \
    DEFAULT_TTTYPES(macro, uchar, uchar) \
    DEFAULT_TTTYPES(macro, short, short) \
    DEFAULT_TTTYPES(macro, ushort, ushort) \
    DEFAULT_TTTYPES(macro, int, int) \
    DEFAULT_TTTYPES(macro, uint, uint) \
    DEFAULT_TTTYPES(macro, long, long) \
    DEFAULT_TTTYPES(macro, ulong, ulong) \
    DEFAULT_TTTYPES(macro, llong, llong) \
    DEFAULT_TTTYPES(macro, ullong, ullong) \
    DEFAULT_TTTYPES(macro, float, float) \
    DEFAULT_TTTYPES(macro, double, double) \
    DEFAULT_TTTYPES(macro, ldouble, ldouble) \
    DEFAULT_TTTYPES(macro, size_t, size_t) 
#endif
