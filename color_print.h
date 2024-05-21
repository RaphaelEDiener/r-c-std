/**
 * print in color
 */

#include <stdio.h>

#ifndef print_redln
// ##############################
// STD OUT
// ##############################

#define print_redln(...) \
    printf ("\x1B[31m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_greenln(...) \
    printf ("\x1B[32m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_blackln(...) \
    printf ("\x1B[30m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_yellowln(...) \
    printf ("\x1B[33m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_blueln(...) \
    printf ("\x1B[34m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_magentyln(...) \
    printf ("\x1B[35m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_cyanln(...) \
    printf ("\x1B[36m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_whiteln(...) \
    printf ("\x1B[37m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m\n");

#define print_red(...) \
    printf ("\x1B[31m"); \
    printf (__VA_ARGS__); \
    printf ("\x1B[0m");

#define print_green(...) \
    printf ("\x1B[32m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1B[0m");

#define print_black(...) \
    printf ("\x1B[30m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1B[0m");

#define print_yellow(...) \
    printf ("\x1B[33m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1B[0m");

#define print_blue(...) \
    printf ("\x1B[34m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1B[0m");

#define print_magenty(...) \
    printf ("\x1B[35m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1B[0m");

#define print_cyan(...) \
    printf ("\x1B[36m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1B[0m");

#define print_white(...) \
    printf ("\x1B[37m"); \
    printf (__VA_ARGS__);  \
    printf ("\x1B[0m");

// ##############################
// ERROR
// ##############################

#define err_redln(...) \
    fprintf (stderr, "\x1B[31m"); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "\x1B[0m\n");

#define err_greenln(...) \
    fprintf (stderr, "\x1B[32m"); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "\x1B[0m\n");

#define err_blackln(...) \
    fprintf (stderr, "\x1B[30m"); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "\x1B[0m\n");

#define err_yellowln(...) \
    fprintf (stderr, "\x1B[33m"); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "\x1B[0m\n");

#define err_blueln(...) \
    fprintf (stderr, "\x1B[34m"); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "\x1B[0m\n");

#define err_magentyln(...) \
    fprintf (stderr, "\x1B[35m"); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "\x1B[0m\n");

#define err_cyanln(...) \
    fprintf (stderr, "\x1B[36m"); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "\x1B[0m\n");

#define err_whiteln(...) \
    fprintf (stderr, "\x1B[37m"); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "\x1B[0m\n");

#define err_red(...) \
    fprintf (stderr, "\x1B[31m"); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "\x1B[0m");

#define err_green(...) \
    fprintf (stderr, "\x1B[32m"); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, "\x1B[0m");

#define err_black(...) \
    fprintf (stderr, "\x1B[30m"); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, "\x1B[0m");

#define err_yellow(...) \
    fprintf (stderr, "\x1B[33m"); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, "\x1B[0m");

#define err_blue(...) \
    fprintf (stderr, "\x1B[34m"); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, "\x1B[0m");

#define err_magenty(...) \
    fprintf (stderr, "\x1B[35m"); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, "\x1B[0m");

#define err_cyan(...) \
    fprintf (stderr, "\x1B[36m"); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, "\x1B[0m");

#define err_white(...) \
    fprintf (stderr, "\x1B[37m"); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, "\x1B[0m");

#endif
