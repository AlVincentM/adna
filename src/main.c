#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "util.h"


int main(int argc, char * argv[]) {

	array = (int*)malloc(sizeof(int));
	temp_array = (int*)malloc(sizeof(int));

	if (NULL == array) {
		perror("Insufficient memory...\n");
		return EXIT_FAILURE;
	}

	prompt();
	usage();

    while(1) {

		char *line = malloc(256 * sizeof(char));

		// user input
    	printf(ANSI_COLOR_CYAN "Quarantine> " ANSI_COLOR_RESET);
    	fgets(line, 256, stdin);

    	// arg_v count
    	int arg_count = 0;

    	// array of arguments with maximum of 50 elements
    	char *arg_vector[50];

    	// parse string into array of strings
    	getArgVector(line, &arg_count, arg_vector);

		if(strcmp(line , "\n") ==  0) {
			continue;
		}

		// quit
		if(strcmp(line, "quit\n") == 0) {
			printf(ANSI_COLOR_GREEN "\nBye!\n\n" ANSI_COLOR_RESET);

			// free all allocated memories
			free(array);
			free(temp_array);
			free(line);
			exit(1);
		}
		else if (strcmp(line, "help\n") == 0) {
			usage();
		}

		else if(strcmp(line, "about\n") == 0) {
			about();
		}

		// show variables
		else if (strcmp(line, "show\n") == 0) {
			printf("Array size N: %d\n", n);
			printf("X: %d\n", x);
			printf("Array: \n");
			for (int i = 0; i < n; i++) {
				printf("%d ", *(array + i));
			}
			printf("\n\n");
		}

		else if (strcmp(line, "about\n") == 0) {

		}

		else {
			// set variables
			if(strcmp(arg_vector[0], "set") == 0) {
				process_args(arg_count, arg_vector);
				printf("N: %d  X: %d \n\n", n, x);
			}

			// sort the array
			else if(strcmp(arg_vector[0], "sort") == 0) {
				process_args(arg_count, arg_vector);
			}

    		free(line);
    	}
    }

    return 0;
}
