#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "../Leibniz/leibniz.h"
#include "../File/file.h"
#include "./process.h"

double execution_time(clock_t start, clock_t end)
{
	return (double)(end - start) / CLOCKS_PER_SEC;
}

double run_one_process()
{
	clock_t start = clock();

	long double pi = leibniz_approx_pi(0, _MAX_ITERATIONS);
	printf("PI: %.20Lf", pi);

	clock_t end = clock();
	return execution_time(start, end);
}

double run_two_process()
{
	clock_t start = clock();
	pid_t pid;
	pid = fork();

	if (pid == -1) {
		perror("FORK: AN UNEXPECTED ERROR OCCURRED DURING THE FORK");
		exit(EXIT_FAILURE);
	}

	unsigned long max = _MAX_ITERATIONS;
	unsigned long mid = max / 2;
	if (pid == 0) {
		long double partial_pi = leibniz_approx_pi(0, mid);

		FILE *file = open_file("./data/two_process/child.txt", "w");
		write_long_double(partial_pi, file);
		fclose(file);

		exit(EXIT_SUCCESS);
	}

	if (pid != 0) {
		long double partial_pi = leibniz_approx_pi(mid, max);

		FILE *file = open_file("./data/two_process/father.txt", "w");
		write_long_double(partial_pi, file);
		fclose(file);

		wait(NULL);
	}

	FILE *file = open_file("./data/two_process/child.txt", "r");
	long double p1 = read_long_double(file);
	fclose(file);

	file = open_file("./data/two_process/father.txt", "r");
	long double p2 = read_long_double(file);
	fclose(file);

	printf("PI: %.20Lf", p1 + p2);
	clock_t end = clock();

	return execution_time(start, end);
}

double run_four_process()
{
}
