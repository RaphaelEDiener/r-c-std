/**
 * double ended dynamic arrays
 */

#include "result.h"
#include "rmath.h"
#include "default_types.h"
#include "color_print.h"
#include "cmp.h"

// back max = capacity-1
// front min = 0
typedef struct {
    size_t capacity;
    size_t size;
    size_t front_i;
    size_t back_i;
    // size_t count; = back_i - front_i
    int* ptr;
} intDda;

DEFINE_RESULT(intDda);

