#pragma once
#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>

FILE *open_file(char *path_file, char *mode);
void write_long_double(long double number, FILE *file);
long double read_long_double(FILE *file);

#endif // _FILE_H_
