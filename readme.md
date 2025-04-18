# R's Standard Library

```
##############################
       Documentation
##############################

If no clarification is given on the specific type,
it is implemented for all types available in c
using the aliases/shorthands found in default_types.h

If a parameter is not declared 'const', it is getting modified.
Parameters are preferably passed by reference, 
since -03 can turn small references into values, 
but not vise versa for large values (reliably acros compilers).

Naming follows the convention:
<modifyer><function name><for type>

-- Building --

There are 3 modes that change how asserts work,
and with that compile time: 

normal:  gcc rstd.c -Wall -Wextra -c -O3 -fmax-errors=2 -o rstd.o
debug:   gcc rstd.c -Wall -Wextra -c -O3 -fmax-errors=2 -o rstd.o -D DEBUG
release: gcc rstd.c -Wall -Wextra -c -O3 -fmax-errors=2 -o rstd.o -D RELEASE

-- Linking --

normal:  gcc -Wall -Wextra -o main.exe -fmax-errors=2 main.c rstd.o
debug:   gcc -Wall -Wextra -o main.exe -fmax-errors=2 main.c rstd.o -D DEBUG
release: gcc -Wall -Wextra -o main.exe -fmax-errors=2 main.c rstd.o -D RELEASE

It is recommended to use `-fmax-errors=2`,
since the library is heavily dependant on macros,
that can quickly result in compiler diarrhea.

-- Using --

`#include "rstd.h"`

------------------------------
Working with Arrays (array_utils.h):
------------------------------

FOR_EACH (arr, len, fn)                    : fn(t )->void
FOR_EACHP(arr, len, fn)                    : fn(t*)->void
ANY      (arr, len, fn, expr)              : fn(t )->char
ANYP     (arr, len, fn, expr)              : fn(t*)->char
ALL      (arr, len, fn, exp)               : fn(t )->char
ALLP     (arr, len, fn, expr)              : fn(t*)->char
IN       (arr, len, elem, expr) 
MAP      (from, len, fn, target)           : fn(t1 )->t2
MAPP     (from, len, fn, target)           : fn(t1*)->t2
MAP_IP   (arr, len, fn)                    : fn(t )->t
MAP_IPP  (arr, len, fn)                    : fn(t*)->t
FOLD     (arr, len, fn, type, name, start) : fn(start , type )->start
FOLDP    (arr, len, fn, type, name, start) : fn(start , type*)->start
FOLDPP   (arr, len, fn, type, name, start) : fn(start*, type*)->start

------------------------------
Comparing (cmp.h):
------------------------------

The macros for costume implementation work for any struct.

-- Predefined -- 

Compareable = {LESS | EQUAL | GREATER}

Compareable  cmp_<t> (const <t> , const <t> )
char         eq_<t>  (const <t> , const <t> )
char         lt_<t>  (const <t> , const <t> )
char         gt_<t>  (const <t> , const <t> )
Compareable pcmp_<t> (const <t>*, const <t>*)
char        peq_<t>  (const <t>*, const <t>*)
char        plt_<t>  (const <t>*, const <t>*)
char        pgt_<t>  (const <t>*, const <t>*)

=> for all default types

-- Costume --

DEFINE_CMP(t)
IMPL_CMP(t)

------------------------------
Printing (color_print.h):
------------------------------

colors: red, green, black, yellow, blue, mangenta, cyan, white

functions:
<color>()
<color>ln() 
err_<color>()
err_<color>ln()

------------------------------
Type Definitions (default_types.h):
------------------------------

typedef signed   char      schar;
typedef unsigned char      uchar;
typedef unsigned short     ushort;
typedef unsigned int       uint;
typedef unsigned long      ulong;
typedef long     long      llong;
typedef unsigned long long ullong;
typedef long     double    ldouble;

DEFAULT_TYPES      (macro)             -> macro(t1) \ macro(t2) \ ...
DEFAULT_TTYPES     (macro, type)       -> macro(type, t1) \ ...
DEFAULT_FOR_TTYPES (macro)             -> DEFAULT_TTYPES(macro, t1) \ ...
DEFAULT_TTTYPES    (macro, type, epyt) -> macro(epyt, type, t1) \ ...
DEFAULT_FOR_TTTYPES(macro)             -> DEFAULT_TTTYPES(macro, t1, t1) \...

------------------------------
Result (result.h):
------------------------------

ResultType = {SUCCESS, FAILURE}
<t>Res -> {type: SUCCESS | FAILURE; result: t}
DEFINE_RESULT(type) -> creates new Result wrapper
voidRes -> {type: SUCCESS | FAILURE}

------------------------------
Dynamic Arrays (dynamic_array.h):
------------------------------

Arrays hold a size, 
since some types can't deduce their size with `sizeof()`

-- Costume --

DEFINE_MAPDA(type)  -> Defines a map  from type to type
DEFINE_FOLDDA(type) -> Defines a fold from type to type
DEFINE_DA(type)     -> Defines a dynamic- and stack array 
                       with most of the associated functions
IMPL_DA(type)       -> Implements the functionality 
                       that was defined previously

-- Predefined -- 

DA / SA = {capacity; size; count; ptr}

new_sa(name, type, capacity) -> create stack array

<t>DaRes new_<t>Da(const size_t capacity)
<t>DaRes insert_<t>Da (const da*, const <t>  elem)
voidRes  insert_<t>Sa (      sa*, const <t>  elem)
<t>DaRes pinsert_<t>Da(const da*, const <t>* elem)
voidRes  pinsert_<t>Sa(      sa*, const <t>* elem)
<t>Res   get_<t>DA(const <t>DA list, const llong i) -> 
                 returns element at position. 
                 works with negative numbers for backwards traversal.
void     for_each_<t>Da(cons wptr, const fn(<t>*)->void)
void     for_each_<t>Sa(const wptr, const fn(<t>*)->void)
void     reverse_<t>Da(wptr)
char     all_<t>Da(const wptr, const fn(const <t>*)->char)
char     all_<t>Sa(const wptr, const fn(const <t>*)->char)
char     any_<t>Da(const wptr, const fn(const <t>*)->char)
char     any_<t>Sa(const wptr, const fn(const <t>*)->char)
char     in_<t>Da(
             const wptr, 
             const elem*, 
             const eq(const <t>*, const <t>*)->char
         )
char     in_<t>Sa(
             const wptr, 
             const elem*, 
             const eq(const <t>*, const <t>*)->char
         )
char     pin_<t>Da( const wptr, const elem*) -> primitive in
<t>Res   first<t>Da(const wptr, const fn(const <t>*)->char)
<t>DaRes unique_<t>Da(
             const wptr, 
             const eq(const <t>*, const <t>*)->char
         ) -> creates new Da with each element being unique 
void     sort_<t>Da(
             wptr, 
             const cmp(const <t>*, const <t>*)->Compareable
         ) -> quick sort in place
void     radix_<t>Da(wptr) -> implements generic radix for arbitrary data. 
                              sorts in place with 4 buffers
void     mapip_<t>Da(wptr, const fn(const <t>*)-><t>)
void     mapip_<t>Sa(wptr, const fn(const <t>*)-><t>)
<to_t>Da map_<from_t>Da_to_<to_t>Da(
             const from_wptr, 
             const fn(const <from_t>*)-><to_t>
         )
!err!    map_<from_t>Da_to_<to_t>Sa -> !use array utils instead!
<t>      fold_<t>Da(
             const wptr, 
             const fn(const <t>*, const <t>*)-><t>, 
             const start
         )
<to_t>   fold_<from_t>Da_to_<to_t>(
             const from_wptr, 
             const fn(const <to_t>*, const <from_t>*)-><to_t>, 
             const start
         )
<to_t>   fold_<from_t>Sa_to_<to_t>(
             const from_wptr, 
             const fn(const <to_t>*, const <from_t>*)-><to_t>, 
             const start
         )

------------------------------
Rings (rings.h):
------------------------------

-- Costume --

DEFINE_RING(type) -> Defines a ring structure for a given struct 
IMPL_RING(type)   -> Implements the ring functions for a given struct
                     Requires prior `DEFINE_RING` 

-- Predefined -- 

Ring = {capacity; front; back; ptr}
The actual capacity of the ring is always one smaller 
than the given capacity:
given: 8 -> actual: 7 elements at once

<t>RingRes new_<t>Ring    (const size_t capacity)
<t>Ring    insert_<t>Ring (      <t>Ring ring, <t> val) ->
               overrides old values if full
<t>RingRes sinsert_<t>Ring(      <t>Ring ring, <t> val) ->
               only if it doesn't override old values
<t>RingRes pop_<t>Ring    (      <t>Ring ring)
<t>Res     peak_<t>Ring   (const <t>Ring ring) -> last element
size_t     count_<t>Ring  (const <t>Ring ring) -> amount of elements 

------------------------------
Lists (lists.h):
------------------------------

Index access operations work with positive numbers for forward traversal
and negative numbers for backwards traversal.

-- Costume --

DEFINE_DLList(type) -> defines signatures 
                       for a new type of double linked list
IMPL_DLList(type)   -> implements the previously defined signatures

-- Predefined -- 

<t>Ll     new_<t>Ll    (const <t>   value) 
void      free_<t>Ll   (      <t>Ll list) -> frees all elements in the LL
<t>Res    get_<t>LL    (const <t>LL list, const llong i) -> 
size_tRes append_<t>LL (      <t>LL list, const t elem)  -> appends in back
size_tRes prepend_<t>LL(      <t>LL list, const t elem) -> appends in front
voidRes   rem_<t>LL    (      <t>LL list, const size_t i) -> removes @ index
voidRes   del_<t>LL    (      <t>LL list, const <t> elem) -> 
              removes the first element found,
              that matches the given element.

------------------------------
String Operations (str_utils.h):
------------------------------
  
 void  skip_whitespace(FILE* fp);
 int   peak(FILE* fp);
 uchar is_digit(char c);
 uchar is_lower(char c);
 uchar is_upper(char c);

------------------------------
Math (rmath.h):
------------------------------

All predefined 

-- Costume --

IMPL_SWAP(type)     -> implements a swap in place function 
                       for a given datatype
DEFINE_VEC(type)    -> <type>Vec2, ...
DEFINE_MATRIX(type) -> <type>Mat2, ...
MATH_TYPES(macro)   -> macro(<t>Vec2), macro(<t>Vec3), ... 

-- Predefined -- 

void   swap_<t>(<t>*, <t>*)
size_t save_sub(size_t x, size_t y)  -> caps at 0
size_t save_add(size_t x, size_t y) -> caps out at MAX_SIZE

<t>Vec2 {x;y}
<t>Vec3 {x;y;z} 
<t>Vec4 {x;y;z;w} 
<t>Mat2 { type* ptr; size_t x; size_t y; }
<t>Mat3 { type* ptr; size_t x; size_t y; size_t z; }
<t>Mat4 { type* ptr; size_t x; size_t y; size_t z; size_t w; }

add_<t>Vec<n>(const <t>Vec<n>* a, const <t>Vec<n>* b)
sub_<t>Vec<n>(const <t>Vec<n>* a, const <t>Vec<n>* b)
mul_<t>Vec<n>(const <t>Vec<n>* a, const <t>Vec<n>* b)
div_<t>Vec<n>(const <t>Vec<n>* a, const <t>Vec<n>* b)
  
------------------------------
Testing (testing.h):
------------------------------
 
test_costume(
    void* real, 
    void* exprected, 
    fn(void*, void*)->char, 
    fn(void*)->char*, 
    char* msg
)

test_char       (char, char, message)
test_schar      (schar, schar, message)
test_uchar      (uchar, uchar, message)
test_short      (short, short, message)
test_ushort     (ushort, ushort, message)
test_int        (int, int, message)
test_uint       (uint, uint, message)
test_long       (long, long, message)
test_ulong      (ulong, ulong, message)
test_llong      (llong, llong, message)
test_ullong     (ullong, ullong, message)
! float operations round to 4 and double to 8 level precission !
test_float      (float, float, message)
test_double     (double, double, message)
test_ldouble    (ldouble, ldouble, message)
test_Compareable(Compareable, Compareable, message)
test_size_t     (size_t, size_t, message)
```

# Using the Lib

First clone the repository.

```
git clone -b clean --depth 1 git@github.com:RaphaelEDiener/r-c-std.git
```

It is recomended to create a new folder for this inside your project:

```
src
 |-main.c
 |-rstd
   |-...
```

If you don't want to deal with git submodules, 
you can always `rm -rf` the `.git` folder.

In theory you can just `#include "rstd.h"` 
and then compile with `gcc -o main.exe main.c rstd.c` and be good to go.
But the compile times will be long, since the library makes heavy use 
of macro expansion to reduce code duplication.

Instead it is recomended to build the lib once and the link with it:
```
gcc -Wall -Wextra -c -o rstd.o -O3 -fmax-errors=2 rstd.c
gcc -o main.exe main.c rstd.o
```

# Internal Dependencies

![internal_dependencies](internal_dependencies.svg)

# TODO

*  Test...
    *  lists
    *  glibc ops
*  TODO: Whidepointer promotions (with typeof)
*  TODO: Join
*  TODO: Drain da into other da
*  TODO: clear da util func
*  TODO: Split
*  TODO: Curry
    *  Needs to be done at runtime with a struct maintaining stuff.
    *  But how do I pass that stuff into the function pointer?
    *  Can I construct a curry object with a macro which is tailor made for the function?
*  TODO: Iterator
*  TODO: Reduce
*  TODO: lerp
*  TODO: DA radix should also use DA's to avoid stack overflows!
*  TODO: radix should not need to go through the heavily checked insert functions
*  TODO: Hashmaps
*  TODO: Deque
*  TODO: Hashsets
*  TODO: Arraysets
*  TODO: universalize del for DA, SA, LL
*  TODO: impl filter for DA, SA, LL
*  TODO: reduce
*  TODO: copy for all structs
*  TODO: arbitrary long integers
*  TODO: test rings
*  TODO: test first_da
*  TODO: linked datastructure with log n lookpups
*  TODO: test if get on lists works with empty lists
*  TODO: change print macros to inline functions
*  TODO: primitive in and general in can be combined to general byte checks like in radix
*  TODO: radix broken 
*  TODO: print function for arbitrary arrays and costume readable implementation for default types
 
```
// join("hi", "my", "name", "is")
// joinp(&"hi", &"my", &"name", &"is")
// joinwp(wp)
```

#define µ .result
#define ⴵ .result
#define Ⳮ .result
#define Ⲅ .result
#define Ⲋ .result
#define ⲗ .result
#define Ⲡ .result
#define Ⲫ .result
#define Ⲷ .result
#define Ⲽ .result
#define ⴲ .result
#define ⴱ .result
