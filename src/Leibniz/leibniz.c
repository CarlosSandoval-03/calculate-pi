#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./leibniz.h"

long double leibniz_approx_pi(unsigned long start, unsigned long end)
{
	if (start > end) {
		perror("LEIBNIZ: INVALID RANGE");
		exit(EXIT_FAILURE);
	}

	long double x = 0.0;
	for (unsigned long i = start; i < end; i++) {
		x += pow(-1, i) / (2 * i + 1);
	}
	x *= 4;
	return x;
}
