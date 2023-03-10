#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "./Leibniz/leibniz.h"

int main(int argc, char **argv)
{
	long double p1 = leibniz_approx_pi(0, (1e09 / 2));
	long double p2 = leibniz_approx_pi((1e09 / 2) + 1, 1e09);

	long double pi = p1 + p2;
	printf("%.20Lf\n", pi);

	return EXIT_SUCCESS;
}
