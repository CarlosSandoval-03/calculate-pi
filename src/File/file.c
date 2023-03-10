#include <stdio.h>
#include <stdlib.h>
#include "./file.h"

FILE *open_file(char *path_file, char *mode)
{
	FILE *file = fopen(path_file, mode);
	if (file == NULL) {
		perror("FILE: AN ERROR HAS OCCURRED");
		exit(EXIT_FAILURE);
	}

	return file;
}

void write_long_double(long double number, FILE *file)
{
	fprintf(file, "%.20Lf", number);
}

long double read_long_double(FILE *file)
{
	long double number = 0.0;
	fscanf(file, "%Lf", &number);
	return number;
}
