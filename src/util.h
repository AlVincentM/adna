#ifndef UTIL_H

#include <time.h>
#include <stdio.h>

#define UTIL_H
#define MAX_RANGE 10000
#define LENGTH(a) sizeof(a) / sizeof(a[0])

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_CYAN  "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

extern int x;
extern int n;
extern int *array;
extern int *temp_array;
extern clock_t start, end;
extern double cpu_time_used;
extern FILE *file;


#endif


/////////////////////////////////
// utility function prototypes //
/////////////////////////////////

extern void prompt(void);

extern void usage(void);

extern int getArgCount(char *string);

extern void getArgVector(char *string, int *arg_c, char *arg_v[]);

extern void process_args(int arg_c, char *arg_v[]);

extern void generateArray(char option);

extern void showArray(void);

extern void copyArray(void);

extern void sortingTime(int choice);

extern void about();