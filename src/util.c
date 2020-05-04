#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>


#include "util.h"
#include "sort.h"

int n;
int x;
int *array;
int *temp_array;
clock_t start, end;
double cpu_time_used;

/**
 * prints banner "Quarantine"
 * @author Al Vincent
 */
void prompt(void) {
  printf(
    "\n+----------------------------------------------------------------------------------------------------------------------------+"
    "\n|    ___________                                                                                                             |"
    "\n|   /           \\                                                                                                            |"
    "\n|  |     ___     |                                                                      _                                    |"
    "\n|  |    /   \\    |  __    __    ______   __ ____     ______   __ ____     __________   / \\   __ ____      ______             |"
    "\n|  |   |  __ |   | |  |  |  |  /____  \\ |  / __  \\  /____  \\ |  / __  \\  |___    ___|  \\_/  |  / __  \\   /  ___  \\           |"
    "\n|  |   |  \\  \\   | |  |  |  |   ___ | | |   /  |__|  ___ | | |   /  |  |     |  |      __   |   /  |  | |  |___| |           |"
    "\n|  |   \\___\\     | |  |  |  |  / __   | |  /        / __   | |  /   |  |     |  |     |  |  |  /   |  | |  ______/           |"
    "\n|  |            /  |  \\__/  | | |__|  | |  |       | |__|  | |  |   |  |     |  |     |  |  |  |   |  | |  |______           |"
    "\n|   \\_______ \\__\\   \\______/   \\___/|_| |__|        \\___/|_| |__|   |__|     |__|     |__|  |__|   |__|  \\_______/ v.0.0.1   |"
    "\n|                                                                                                                            |"
    "\n+----------------------------------------------------------------------------------------------------------------------------+\n"
  );
}

/**
 * [Parse the string into an argument vector]
 * @author Al Vincent
 * @param  string [description]
 * @param  arg_c  [description]
 * @param  arg_v  [description]
 */
void getArgVector(char *string, int *arg_c, char *arg_v[]) {

  // tokenize string
  char *p = strtok(string, " ");
  int i = 0;

  // until NULL
  while(p != NULL) {
    arg_v[i] = p;

    // tokenize again
    p = strtok(NULL, " ");
    i++;

    // add 1 to arg_c
    *arg_c += 1;
  }
}

/**
 * [process_args description]
 * @author Al Vincent
 * @param  arg_c [description]
 * @param  arg_v [description]
 * @param  n     [description]
 * @param  x     [description]
 */
void process_args(int arg_c, char *arg_v[]) {
    int c;
    
    while(1) {

      int option_index = 0;

      // list of options
      static struct option long_options[] = {
        {"help",    no_argument,        NULL, 'h'},
        {"X",       required_argument,  NULL, 'x'},
        {"N",       required_argument,  NULL, 'n'},
        {"array",   required_argument,  NULL, 'a'},
        {"sort-using",    required_argument,  NULL, 's'},
        {NULL,      0,                  NULL,   0}
      };

      c = getopt_long(arg_c, arg_v, "x:n:a:s:h", long_options, &option_index);
      
      if(c == -1) {

        // reset optind = 0 every after parsing
        optind = 0;
        break;
      }

      switch(c) {
        case 'h': usage();
                  exit(0);
                  break;

        case 'n': n = atoi(optarg);
                  break;

        case 'x': x = atoi(optarg);
                  break;

                  // generates a random array
        case 'a': if (strcmp(optarg, "random") == 0 || strcmp(optarg, "random\n") == 0) {
                    generateArray('r');
                    showArray();
                  }

                  // generates a sorted array
                  else if (strcmp(optarg, "sorted") == 0 || strcmp(optarg, "sorted\n") == 0) {
                    generateArray('s');
                    showArray();
                  }

                  // print an error if provided other arguments
                  else {
                    fprintf(stderr, "[ERROR]: Invalid argument for --array\n");
                  }
                  break;

        case 's': if (strcmp(optarg, "insertionsort") == 0 || strcmp(optarg, "insertionsort\n") == 0) {
                    copyArray();
                    sortingTime(1);
                  }

                  else if (strcmp(optarg, "mergesort") == 0 || strcmp(optarg, "mergesort\n") == 0) {
                    copyArray();
                    sortingTime(2);
                  }

                  else if (strcmp(optarg, "quicksort") == 0 || strcmp(optarg, "quicksort\n") == 0) {
                    // TODO: sort with quick sort
                  }

                  else if (strcmp(optarg, "heapsort") == 0 || strcmp(optarg, "heapsort\n") == 0) {
                    // TODO: sort with heap sort
                  }

                  else {
                    fprintf(stderr,
                            "[ERRO]: Unrecognized params for -s/--sort-using\n"
                            "Use sort -h for help\n\n"
                            );
                  }
                  break;

        case '?': printf("Unknown option %c\n", optopt);
                  break;
        case ':': printf("Missing argument for %c\n", optopt);
      }

    } 
    

    return;
}

/**
 * [The help message]
 * @author Al Vincent
 */
void usage(void) {
    fprintf(stderr, 
        "Usage:\n"
        "   SET [-n arraysize] [-x xsize] [-h]\n"
        "       -h:     print help message\n"
        "       -n:     array size N\n"
        "       -x:     elements multiplier X\n"
        "\n"
    );
}

/**
 * generate array
 * @author Al Vincent
 * @param  n [array size as N]
 * @param  x [multiplier as X]
 */
void generateArray(char option) {

  // allocate memory
  array = realloc(array, n * sizeof(int));

  // return if reallocation is unsuccessful
  if(NULL == array) {
    fprintf(stderr, "[ERROR]: Array size not set or insufficient memory.\n");
    free(array);
    return;
  }

  // make array random if option is r
  if (option == 'r') {

    for (int i = 0; i < n; i++) {
      *(array + i) = rand() % MAX_RANGE + 1;
    }
    printf("Array generated!\n");
  }

  // make array sorted if option is s
  else if (option == 's') {
    int num = 1;
    for(int i = 0; i < n; i++) {
      *(array + i) = n + (num * x);
      num++;
    }
    printf("Array generated!\n");
  }
}

/**
 * [showArray description]
 * @author Al Vincent
 */
void showArray(void) {

  // print array
  for (int i = 0; i < n; i++) {
    printf("%d ", *(array + i));
  }
  printf("\n");
}

/**
 * [copyArray description]
 * @author Al Vincent
 */
void copyArray(void) {

  // realloc temp_array
  temp_array = realloc(temp_array, n * sizeof(int));
  if (NULL == temp_array) {
    fprintf(stderr, "Reallocation failed. Maybe insufficient memory.\n");
    free(temp_array);
    return;
  }

  // copy
  for (int i = 0; i < n; i++) {
    *(temp_array + i) = *(array + i);
  }
}

void sortingTime(int choice) {

  switch(choice) {

            // get T(N) for insertion sort
    case 1: start = clock();
            insertionSort();
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nBEFORE:\n");
            showArray();
            printf("\n");
            printf("AFTER:\n");
            for (int i = 0; i < n; i++) {
              printf("%d ", *(temp_array + i));
            }
            printf("\n\n");
            printf( "------------------------------------\n"
                    "Insertion Sort took %f seconds\n"
                    "------------------------------------\n\n"
                    , cpu_time_used);
            break;

            // get T(N) for merge sort
    case 2: start = clock();
            mergeSort(0, n - 1);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("\nBEFORE:\n");
            showArray();
            printf("\n");
            printf("AFTER:\n");
            for (int i = 0; i < n; i++) {
              printf("%d ", *(temp_array + i));
            }
            printf("\n\n");
            printf( "--------------------------------\n"
                    "Merge Sort took %f seconds\n"
                    "--------------------------------\n\n"
                    , cpu_time_used);
            break;

  }
}