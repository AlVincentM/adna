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
FILE *file;

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
                  break;

        case 'n': n = atoi(optarg);
                  break;

        case 'x': x = atoi(optarg);
                  break;

                  // generates a random array
        case 'a': if (strcmp(optarg, "random") == 0 || strcmp(optarg, "random\n") == 0) {
                    generateArray('r');
                  }

                  // generates a sorted array
                  else if (strcmp(optarg, "sorted") == 0 || strcmp(optarg, "sorted\n") == 0) {
                    generateArray('s');
                  }

                  // print an error if provided other arguments
                  else {
                    fprintf(stderr, "\n[ERROR]: Invalid argument for --array\n\n");
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
                    copyArray();
                    sortingTime(3);
                  }

                  else if (strcmp(optarg, "heapsort") == 0 || strcmp(optarg, "heapsort\n") == 0) {
                    copyArray();
                    sortingTime(4);
                  }

                  else {
                    fprintf(stderr,
                            "\n"
                            "[ERROR]: Unrecognized params for -s/--sort-using\n"
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
        "   COMMANDS:\n"
        "   set [-n arraysize] [-x xsize] [-a random|sorted] [--array=random|sorted] [-h]\n\n"
        "       -h                    print help message\n"
        "       -n <number>           set array size N\n"
        "       -x <number>           set multiplier X\n"
        "       -a random|sorted      set array to either random or sorted\n"
        "       --array=random|sorted                                     \n"
        "\n"
        "   sort [-s insertionsort|mergesort|quicksort|heapsort] [-h]\n\n"
        "       -h                    print help message\n"
        "       -s insertionsort|mergesort|quicksort|heapsort \n"
        "       --sort-using=insertionsort|mergesort|quicksort|heapsort\n"
        "                             sort the array using any of the given sorting algorithms\n"
        "\n"
        "   show                      show the values of N, X, and array elements\n"
        "\n"
        "   about                     prints the details about the program\n"
        "\n"
        "   quit                      quit the program\n"
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
    fprintf(stderr, "[ERROR]: Array size not set or insufficient memory.\n\n");
    free(array);
    return;
  }

  // make array random if option is r
  if (option == 'r') {
    srand(time(0));
    for (int i = 0; i < n; i++) {
      *(array + i) = rand() % MAX_RANGE + 1;
    }
    printf("\nArray generated!\n");
  }

  // make array sorted if option is s
  else if (option == 's') {
    int num = 1;
    for(int i = 0; i < n; i++) {
      *(array + i) = n + (num * x);
      num++;
    }
    printf("\nArray generated!\n");
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

  FILE *file = fopen("OUTPUT.txt", "a");
  time_t rawtime;
  struct tm *timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  switch(choice) {

            // get T(N) for insertion sort
    case 1: start = clock();
            insertionSort();
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

            // print to file
            fprintf(file, 
                    "[%02d-%02d-%02d %02d:%02d:%02d] Sorting array of %d elements...\n",
                    timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, n);
            fprintf(file, "BEFORE:\n");
            for (int i = 0; i < n; i++) {
              fprintf(file, "%d ", *(array + i));
            }
            fprintf(file, "\n");
            fprintf(file, "\nAFTER:\n");
            for (int i = 0; i < n; i++) {
              fprintf(file, "%d ", *(temp_array + i));
            }
            fprintf(file, "\n\n");
            fprintf(file,
                    "------------------------------------\n"
                    "Insertion Sort took %f seconds\n"
                    "------------------------------------\n\n"
                    , cpu_time_used);

            // print to screen
            printf( "\n"
                    "------------------------------------\n"
                    "Insertion Sort took %f seconds\n"
                    "------------------------------------\n\n"
                    , cpu_time_used);
            break;

            // get T(N) for merge sort
    case 2: start = clock();
            mergeSort(0, n - 1);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

            // print to file
            fprintf(file, 
                    "[%02d-%02d-%02d %02d:%02d:%02d] Sorting array of %d elements...\n",
                    timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, n);
            fprintf(file, "BEFORE:\n");
            for (int i = 0; i < n; i++) {
              fprintf(file, "%d ", *(array + i));
            }
            fprintf(file, "\n");
            fprintf(file, "\nAFTER:\n");
            for (int i = 0; i < n; i++) {
              fprintf(file, "%d ", *(temp_array + i));
            }
            fprintf(file, "\n\n");
            fprintf(file,
                    "--------------------------------\n"
                    "Merge Sort took %f seconds\n"
                    "--------------------------------\n\n"
                    , cpu_time_used);

            // print to screen
            printf( "\n"
                    "--------------------------------\n"
                    "Merge Sort took %f seconds\n"
                    "--------------------------------\n\n"
                    , cpu_time_used);
            break;

    case 3: start = clock();
            quickSort(0, n - 1);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

            // print to file
            fprintf(file, 
                    "[%02d-%02d-%02d %02d:%02d:%02d] Sorting array of %d elements...\n",
                    timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, n);
            fprintf(file, "BEFORE:\n");
            for (int i = 0; i < n; i++) {
              fprintf(file, "%d ", *(array + i));
            }
            fprintf(file, "\n");
            fprintf(file, "\nAFTER:\n");
            for (int i = 0; i < n; i++) {
              fprintf(file, "%d ", *(temp_array + i));
            }
            fprintf(file, "\n\n");
            fprintf(file,
                    "--------------------------------\n"
                    "Quick Sort took %f seconds\n"
                    "--------------------------------\n\n"
                    , cpu_time_used);

            // print to screen
            printf( "\n"
                    "--------------------------------\n"
                    "Quick Sort took %f seconds\n"
                    "--------------------------------\n\n"
                    , cpu_time_used);
            break;

    case 4: start = clock();
            heapSort();
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

            // print to file
            fprintf(file, 
                    "[%02d-%02d-%02d %02d:%02d:%02d] Sorting array of %d elements...\n",
                    timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, n);
            fprintf(file, "BEFORE:\n");
            for (int i = 0; i < n; i++) {
              fprintf(file, "%d ", *(array + i));
            }
            fprintf(file, "\n");
            fprintf(file, "\nAFTER:\n");
            for (int i = 0; i < n; i++) {
              fprintf(file, "%d ", *(temp_array + i));
            }
            fprintf(file, "\n\n");
            fprintf(file,
                    "-------------------------------\n"
                    "Heap Sort took %f seconds\n"
                    "-------------------------------\n\n"
                    , cpu_time_used);

            // print to screen
            printf( "\n"
                    "-------------------------------\n"
                    "Heap Sort took %f seconds\n"
                    "-------------------------------\n\n"
                    , cpu_time_used);
            break;

  }
  
  fclose(file);
}

void about() {
  printf(
          ANSI_COLOR_GREEN
          "\n"
          "+--------------------------------------------------------------------------------------------------+\n"
          "| This program computes the sorting time of Insertion Sort, Merge Sort, Quick Sort, and Heap Sort. |\n"
          "| Written by: Al Vincent Musa, BSCS-2B CS-111 Algorithm Design and Analysis                        |\n"
          "+--------------------------------------------------------------------------------------------------+\n"
          "\n"
          ANSI_COLOR_RESET
        );
}