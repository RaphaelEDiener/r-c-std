/**
 * print in color
 */

#include <stdio.h>

#ifndef redln

extern const char* TERM_CLEAR;
extern const char* TERM_BLACK;
extern const char* TERM_RED;
extern const char* TERM_GREEN;
extern const char* TERM_YELLOW;
extern const char* TERM_BLUE;
extern const char* TERM_MAGENTA;
extern const char* TERM_CYAN;
extern const char* TERM_WHITE;

// ##############################
// STD OUT
// ##############################

#define redln(...) \
    printf (TERM_RED); \
    printf (__VA_ARGS__); \
    printf ("%s\n", TERM_CLEAR);

#define greenln(...) \
    printf (TERM_GREEN); \
    printf (__VA_ARGS__); \
    printf ("%s\n", TERM_CLEAR);

#define blackln(...) \
    printf (TERM_BLACK); \
    printf (__VA_ARGS__); \
    printf ("%s\n", TERM_CLEAR);

#define yellowln(...) \
    printf (TERM_YELLOW); \
    printf (__VA_ARGS__); \
    printf ("%s\n", TERM_CLEAR);

#define blueln(...) \
    printf (TERM_BLUE); \
    printf (__VA_ARGS__); \
    printf ("%s\n", TERM_CLEAR);

#define magentaln(...) \
    printf (TERM_MAGENTA); \
    printf (__VA_ARGS__); \
    printf ("%s\n", TERM_CLEAR);

#define cyanln(...) \
    printf (TERM_CYAN); \
    printf (__VA_ARGS__); \
    printf ("%s\n", TERM_CLEAR);

#define whiteln(...) \
    printf (TERM_WHITE); \
    printf (__VA_ARGS__); \
    printf ("%s\n", TERM_CLEAR);

#define out_red(...) \
    printf (TERM_RED); \
    printf (__VA_ARGS__); \
    printf (TERM_CLEAR);

#define out_green(...) \
    printf (TERM_GREEN); \
    printf (__VA_ARGS__);  \
    printf (TERM_CLEAR);

#define out_black(...) \
    printf (TERM_BLACK); \
    printf (__VA_ARGS__);  \
    printf (TERM_CLEAR);

#define out_yellow(...) \
    printf (TERM_YELLOW); \
    printf (__VA_ARGS__);  \
    printf (TERM_CLEAR);

#define out_blue(...) \
    printf (TERM_BLUE); \
    printf (__VA_ARGS__);  \
    printf (TERM_CLEAR);

#define out_magenta(...) \
    printf (TERM_MAGENTA); \
    printf (__VA_ARGS__);  \
    printf (TERM_CLEAR);

#define out_cyan(...) \
    printf (TERM_CYAN); \
    printf (__VA_ARGS__);  \
    printf (TERM_CLEAR);

#define out_white(...) \
    printf (TERM_WHITE); \
    printf (__VA_ARGS__);  \
    printf (TERM_CLEAR);

// ##############################
// ERROR
// ##############################

#define err_redln(...) \
    fprintf (stderr, TERM_RED); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "%s\n", TERM_CLEAR);

#define err_greenln(...) \
    fprintf (stderr, TERM_GREEN); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "%s\n", TERM_CLEAR);

#define err_blackln(...) \
    fprintf (stderr, TERM_BLACK); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "%s\n", TERM_CLEAR);

#define err_yellowln(...) \
    fprintf (stderr, TERM_YELLOW); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "%s\n", TERM_CLEAR);

#define err_blueln(...) \
    fprintf (stderr, TERM_BLUE); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "%s\n", TERM_CLEAR);

#define err_magentaln(...) \
    fprintf (stderr, TERM_MAGENTA); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "%s\n", TERM_CLEAR);

#define err_cyanln(...) \
    fprintf (stderr, TERM_CYAN); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "%s\n", TERM_CLEAR);

#define err_whiteln(...) \
    fprintf (stderr, TERM_WHITE); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, "%s\n", TERM_CLEAR);

#define err_red(...) \
    fprintf (stderr, TERM_RED); \
    fprintf (stderr, __VA_ARGS__); \
    fprintf (stderr, TERM_CLEAR);

#define err_green(...) \
    fprintf (stderr, TERM_GREEN); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, TERM_CLEAR);

#define err_black(...) \
    fprintf (stderr, TERM_BLACK); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, TERM_CLEAR);

#define err_yellow(...) \
    fprintf (stderr, TERM_YELLOW); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, TERM_CLEAR);

#define err_blue(...) \
    fprintf (stderr, TERM_BLUE); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, TERM_CLEAR);

#define err_magenta(...) \
    fprintf (stderr, TERM_MAGENTA); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, TERM_CLEAR);

#define err_cyan(...) \
    fprintf (stderr, TERM_CYAN); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, TERM_CLEAR);

#define err_white(...) \
    fprintf (stderr, TERM_WHITE); \
    fprintf (stderr, __VA_ARGS__);  \
    fprintf (stderr, TERM_CLEAR);

#endif
