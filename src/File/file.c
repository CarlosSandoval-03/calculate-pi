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

void write_partial_pi(char *path, long double partial_pi)
{
	FILE *file = open_file(path, "w");
	write_long_double(partial_pi, file);
	fclose(file);
}

long double read_partials_pi(char *path_array[], int num_elements)
{
	long double pi = 0.0;
	FILE *file = NULL;
	for (int i = 0; i < num_elements; i++) {
		file = open_file(path_array[i], "r");
		pi += read_long_double(file);
		fclose(file);
	}

	return pi;
}
