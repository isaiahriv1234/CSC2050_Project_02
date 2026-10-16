#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void unique_lines(FILE *input) {
	char *current = NULL;
	char *previous = NULL;
	size_t current_size = 0;
	size_t previous_size = 0;
	int first_line = 1;

	while (getline(&current, &current_size, input) != -1) {
		if (first_line || strcmp(current, previous) != 0) {
			fputs(current, stdout);
		}

		char *temp_line = current;
		size_t temp_size = current_size;
		
		current = previous;
		current_size = previous_size;

		previous = temp_line;
		previous_size = temp_size;

		first_line = 0;
	}

	free(current);
	free(previous);
}

int main(int argc, char *argv[]) {
	FILE *input = stdin;

	if (argc > 2) {
		fprintf(stderr, "Usage: %s [file]\n", argv[0]);
		return 1;
	}

	if (argc == 2) {
		input = fopen(argv[1], "r");

		if (input == NULL) {
		    perror(argv[1]);
		    return 1;
		}
	}

	unique_lines(input);

	if (input != stdin) {
		fclose(input);
	}

	return 0;
}
