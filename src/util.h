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

void prompt(void);
void usage(void);

int getArgCount(char *string);

void getArgVector(char *string, int *arg_c, char *arg_v[]);

void process_args(int arg_c, char *arg_v[]);