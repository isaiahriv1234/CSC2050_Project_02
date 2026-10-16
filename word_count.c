#include <stdio.h>
#include <ctype.h>

void word_count(FILE *input, int *lines, int *words, int *chars) {
	int ch;
	int in_word = 0;

	*lines = 0;
	*words = 0;
	*chars = 0;

	while ((ch = fgetc(input)) != EOF) {
		(*chars)++;

		if (ch == '\n') {
		    (*lines)++;
		}

		if (isspace(ch)) {
	            in_word = 0;
		} 

		else if (!in_word) {
	          (*words)++;
		  in_word = 1;
		}
	}
}


int main(int argc, char *argv[]) {
	FILE *input = stdin;
	int lines, words, chars;

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

	word_count(input, &lines, &words, &chars);

	printf("%d %d %d\n", lines, words, chars);

	if (input != stdin) {
           fclose(input);
	}


	return 0;
}
