#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "util.h"

int n;
int x;
int *array;

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

        c = getopt(arg_c, arg_v, "hn:x:");

        if(c == -1) {
            optind = 0;
            break;
        }

        switch(c) {
                      // print help message
            case 'h': usage();
                      exit(0);
                      break;

                      // set N as array size
            case 'n': n = atoi(optarg);
                      break;

                      // set X for option b
            case 'x': x = atoi(optarg);
                      break;

                      // print error if no argument is provided
            case ':': fprintf(stderr, "\n Error: -%c missing argument\n", optopt);
                      usage();
                      exit(1);
                      break;
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