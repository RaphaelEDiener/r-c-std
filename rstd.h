#ifndef RSTD
#define RSTD

#include "array_utils.h"
#include "color_print.h"
#include "dynamic_array.h"
#include "default_types.h"
#include "result.h"
#include "testing.h"
#include "str_utils.h"
#include "lists.h"

#endif

/** 
 * ##############################
 *        Documentation
 * ##############################
 *
 * If no clarification is given on the specific type,
 * it is implemented for all types available in c
 * using the aliases/shorthands found in default_types.h
 *
 * if a parameter is not declared 'const', it is getting modified.
 *
 * Linking: rstd.c 
 *
 * ------------------------------
 * Working with Arrays (array_utils.h):
 * ------------------------------
 * 
 * FOR_EACH (arr, len, fn)                    : fn(t)->void
 * FOR_EACHP(arr, len, fn)                    : fn(t*)->void
 * ANY      (arr, len, fn, expr)              : fn(t)->char
 * ANYP     (arr, len, fn, expr)              : fn(t*)->char
 * ALL      (arr, len, fn, exp)               : fn(t)->char
 * ALLP     (arr, len, fn, expr)              : fn(t*)->char
 * IN       (arr, len, elem, expr) 
 * MAP      (from, len, fn, target)           : fn(t1)->t2
 * MAPP     (from, len, fn, target)           : fn(t1*)->t2
 * MAP_IP   (arr, len, fn)                    : fn(t)->t
 * MAP_IPP  (arr, len, fn)                    : fn(t*)->t
 * FOLD     (arr, len, fn, type, name, start) : fn(start, type)->start
 * FOLDP    (arr, len, fn, type, name, start) : fn(start, type*)->start
 * FOLDPP   (arr, len, fn, type, name, start) : fn(start*, type*)->start
 *
 * ------------------------------
 * Comparing (cmp.h):
 * ------------------------------
 *
 * Compareable = {LESS | EQUAL | GREATER}
 *
 * Compareable cmp_<type> (const <type>*, const <type>*)
 * char        eq_<type>  (const <type>*, const <type>*)
 *
 * => for all default types
 *
 * ------------------------------
 * Printing (color_print.h):
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
 * IMPL_DA(type)     -> Implements the functionality that was defined previously
 *
 * -- Predefined -- 
 *
 * DA / SA = {capacity; size; count; ptr}
 *
 * new_sa(name, type, capacity) -> create stack array
 * 
 * <type>DaRes new_<type>Da(const size_t capacity)
 * <type>DaRes insert_<type>Da(const wprt, const elem)
 * voidRes     insert_<type>Sa(wprt, const elem)
 * void        for_each_<type>Da(wptr, const fn(<type>*)->void)
 * void        for_each_<type>Sa(wptr, const fn(<type>*)->void)
 * char        all_<type>Da(wptr, const fn(const <type>*)->char)
 * char        all_<type>Sa(wptr, const fn(const <type>*)->char)
 * char        any_<type>Da(wptr, const fn(const <type>*)->char)
 * char        any_<type>Sa(wptr, const fn(const <type>*)->char)
 * char        in_<type>Da(const wptr, const elem*, const eq(const <type>*, const <type>*)->char)
 * char        in_<type>Sa(const wptr, const elem*, const eq(const <type>*, const <type>*)->char)
 * char        pin_<type>Da(const wptr, const elem*) -> primitive in
 * <type>DaRes unique_<type>Da(const wptr, const eq(const <type>*, const <type>*)->char)
 * void        sort_<type>Da(wptr, const cmp(const <type>*, const <type>*)->Compareable) -> quick sort in place
 * void        radix_<type>Da(wptr) -> implements generic radix for arbitrary data. 
 *                                     sorts in place with 4 buffers
 * void        mapip_<type>Da(wptr, const fn(const <type>*)-><type>)
 * void        mapip_<type>Sa(wptr, const fn(const <type>*)-><type>)
 * <to_t>Da    map_<from_t>Da_to_<to_t>Da(from_wptr, const fn(const <from_t>*)-><to_t>)
 * !err!       map_<from_t>Da_to_<to_t>Sa -> !use array utils instead!
 * <to_t>      fold_<from_t>Da_to_<to_t>(const from_wptr, const fn(const <to_t>*, const <from_t>*)-><to_t>, const start)
 * <to_t>      fold_<from_t>Sa_to_<to_t>(const from_wptr, const fn(const <to_t>*, const <from_t>*)-><to_t>, const start)
 * 
 * ------------------------------
 * Lists (lists.h):
 * ------------------------------
 * 
 * -- Costume --
 * 
 * DEFINE_DLList(type) -> defines signatures for a new type of double linked list
 * IMPL_DLList(type)   -> implements the previously defined signatures
 * 
 * -- Predefined -- 
 * 
 * size_tRes append_<type>LL(<type>LL list, t elem)  -> appends in back
 * size_tRes prepend_<type>LL(<type>LL list, t elem) -> appends in front
 * <type>Res get_<type>LL(<type>LL list, long long i) -> returns element at position. 
 *                                     works with negative numbers for backwards traversal.
 * voidRes   rem_<type>LL(<type>LL list, size_t i) -> removes the element at a given position.
 *                                     works with negative numbers for backwards traversal.
 * voidRes   del_<type>LL(<type>LL list, <type> elem) -> removes the first element found,
 *                                     that matches the given element.
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
 * Math (rmath.h):
 * ------------------------------
 *
 * -- Costume --
 *
 * IMPL_SWAP(type)  -> implements a swap in place function for a given datadype
 *                  -> swap_<type>(<type>*, <type>*)
 * DEFINE_VEC2(type) 
 * DEFINE_VEC3(type) 
 * DEFINE_VEC4(type) 
 *
 * -- Predefined -- 
 *
 * size_t save_sub(size_t x, size_t y)  -> caps at 0
 * size_t save_add(size_t x, size_t y) -> caps out at MAX_SIZE
 *
 * <type>Vec2 {x;y}
 * <type>Vec3 {x;y;z} 
 * <type>Vec4 {x;y;z;w} 
 * <type>Mat { type* ptr; size_t x; size_t y; }
 * <type>Mat { type* ptr; size_t x; size_t y; size_t z; }
 * <type>Mat { type* ptr; size_t x; size_t y; size_t z; size_t w; }
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
 * test_Compareable(Compareable, Compareable, message)
 * test_size_t     (size_t, size_t, message)
 * 
 */
