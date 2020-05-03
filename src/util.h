#ifndef UTIL_H

#define UTIL_H
#define MAX_RANGE 10000
#define LENGTH(a) sizeof(a) / sizeof(a[0])

extern int x;
extern int n;
extern int *array;


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

extern void showArray();