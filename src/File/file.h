#pragma once
#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>

FILE *open_file(char *path_file, char *mode);
void write_long_double(long double number, FILE *file);
long double read_long_double(FILE *file);
void write_partial_pi(char *path, long double partial_pi);
long double read_partials_pi(char *path_array[], int num_elements);

#endif // _FILE_H_
