#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "util.h"


int main(int argc, char * argv[]) {

    prompt();

    while(1) {
        char * line = readline("Quarantine > ");
        if(!line) break;
        if(*line) add_history(line);
        /* Do something with the line here */
        free(line);
    }

    return 0;
}