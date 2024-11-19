#include "rmath.h"

DEFAULT_TYPES(IMPL_SWAP)
MATH_TYPES(IMPL_SWAP)

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

DEFAULT_TYPES(IMPL_VEC);
MATH_TYPES(IMPL_CMP);

// wip
// char brk(double curr, double target){
//     return (curr >= target);
// }
// double step(double curr, double add){
//     return curr + add;
// }
// intIterator lerp(int start, int end) {
//     int_doubleIterator ans = {end, start, };
// }
