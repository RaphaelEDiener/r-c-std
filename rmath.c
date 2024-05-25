#include "rmath.h"

void swap(uchar* p1, uchar* p2) {
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
}

size_t save_sub(size_t x, size_t y) {
    size_t min = x - y;
    return min > x ? 0 : min;
}
size_t save_add(size_t x, size_t y) {
    size_t max = x + y;
    return max < x ? SIZE_MAX : max;
}
