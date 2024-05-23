#ifndef RSTD
#define RSTD

#include "array_utils.h"
#include "color_print.h"
#include "dynamic_array.h"
#include "default_types.h"
#include "result.h"
#include "testing.h"
#include "str_utils.h"

#endif

/** 
 * ##############################
 *        Documentation
 * ##############################
 *
 * Linking: dynamic_array.c str_utils.c testing.c
 *
 * ------------------------------
 * Working with Arrays (array_utils.h):
 * ------------------------------
 * 
 * FOR_EACH(arr, len, fn) : fn(t)->void
 * FOR_EACHP(arr, len, fn) : fn(t*)->void
 * ANY(arr, len, fn, expr) : fn(t)->char
 * ANYP(arr, len, fn, expr) : fn(t*)->char
 * ALL(arr, len, fn, exp) : fn(t)->char
 * ALLP(arr, len, fn, expr) : fn(t*)->char
 * IN(arr, len, elem, expr) 
 * MAP(from, len, fn, target) : fn(t1)->t2
 * MAPP(from, len, fn, target) : fn(t1*)->t2
 * MAP_IP(arr, len, fn) : fn(t)->t
 * MAP_IPP(arr, len, fn) : fn(t*)->t
 * FOLD(arr, len, fn, type, name, start) : fn(start, t)->start
 * FOLDP(arr, len, fn, type, name, start) : fn(start, t*)->start
 *
 * ------------------------------
 * Printing (color_print):
 * ------------------------------
 * 
 * colors: red, green, black, yellow, blue, mangenta, cyan, white
 *
 * functions:
 * <color>()
 * <color>ln() 
 * err_<color>()
 * err_<color>ln()
 *
 * ------------------------------
 * Type Definitions (default_types.h):
 * ------------------------------
 *
 * typedef signed char schar;
 * typedef unsigned char uchar;
 * typedef unsigned short ushort;
 * typedef unsigned int uint;
 * typedef unsigned long ulong;
 * typedef long long long_long;
 * typedef unsigned long long ulong_long;
 * typedef long double long_double;
 *
 * DEFAULT_TYPES(macro) -> macro(t1) \ macro(t2) \ ...
 * DEFAULT_TTYPES(macro, type) -> macro(type, t1) \ ...
 * DEFAULT_FOR_TTYPES(macro) -> DEFAULT_TTYPES(macro, t1) \ ...
 * DEFAULT_TTTYPES(macro, type, epyt) -> macro(epyt, type, t1) \ ...
 * DEFAULT_FOR_TTTYPES(macro) -> DEFAULT_TTTYPES(macro, t1, t1) \ ...
 *
 * ------------------------------
 * Dynamic Arrays (dynamic_array.h):
 * ------------------------------
 *
 * -- Costume --
 *
 * DEFINE_MAPDA(type)  -> Defines a map from type to type
 * DEFINE_FOLDDA(type) -> Defines a fold from type to type
 * DEFINE_DA(type)     -> Defines a dynamic- and stack array with most of the associated functions
 *
 * -- Predefined -- 
 *
 * DA / SA = {capacity; size; count; ptr}
 *
 * new_da(name, type, capacity) -> create heap array
 * new_sa(name, type, capacity) -> create stack array
 * 
 * <type>DaRes insert_<type>Da(wprt, elem)
 * voidRes     insert_<type>Sa(wprt, elem)
 * void        for_each_<type>Da(wptr, fn(<type>*)->void)
 * void        for_each_<type>Sa(wptr, fn(<type>*)->void)
 * char        all_<type>Da(wptr, fn(<type>*)->char)
 * char        all_<type>Sa(wptr, fn(<type>*)->char)
 * char        any_<type>Da(wptr, fn(<type>*)->char)
 * char        any_<type>Sa(wptr, fn(<type>*)->char)
 * char        in_<type>Da(wptr, elem*, fn(<type>*,<type>*)->char)
 * char        in_<type>Sa(wptr, elem*, fn(<type>*,<type>*)->char)
 * void        mapip_<type>Da(wptr, fn(<type>*)-><type>)
 * void        mapip_<type>Sa(wptr, fn(<type>*)-><type>)
 * <to_t>Da    (from_wptr, fn(<from_t>*)-><to_t>)
 * !err!       map_<from_t>Da_to_<to_t>Da -> !use array utils instead!
 * <to_t>      fold_<from_t>Da_to_<to_t>(from_wptr, fn(<to_t>*, <from_t>*)-><to_t>, start)
 * <to_t>      fold_<from_t>Sa_to_<to_t>(from_wptr, fn(<to_t>*, <from_t>*)-><to_t>, start)
 * 
 * ------------------------------
 * Result (result.h):
 * ------------------------------
 * 
 * ResultType = {SUCCESS, FAILURE}
 * <t>Res -> {type: SUCCESS | FAILURE; result: t}
 * DEFINE_RESULT(type) -> creates new Result wrapper
 * voidRes -> {type: SUCCESS | FAILURE}
 *
 * ------------------------------
 * String Operations (str_utils.h):
 * ------------------------------
 *   
 *  void  skip_whitespace(FILE* fp);
 *  int   peak(FILE* fp);
 *  uchar is_digit(char c);
 *  uchar is_lower(char c);
 *  uchar is_upper(char c);
 *   
 * ------------------------------
 * Testing (testing.h):
 * ------------------------------
 *  
 * test_costume(
 *     void* real, 
 *     void* exprected, 
 *     fn(void*, void*)->char, 
 *     fn(void*)->char*, 
 *     char* msg
 * )
 *
 * test_char       (char, char, message)
 * test_schar      (schar, schar, message)
 * test_uchar      (uchar, uchar, message)
 * test_short      (short, short, message)
 * test_ushort     (ushort, ushort, message)
 * test_int        (int, int, message)
 * test_uint       (uint, uint, message)
 * test_long       (long, long, message)
 * test_ulong      (ulong, ulong, message)
 * test_long_long  (long_long, long_long, message)
 * test_ulong_long (ulong_long, ulong_long, message)
 * ! float operations round to 4 and double to 8 level precission !
 * test_float      (float, float, message)
 * test_double     (double, double, message)
 * test_long_double(long_double, long_double, message)
 * 
 */
