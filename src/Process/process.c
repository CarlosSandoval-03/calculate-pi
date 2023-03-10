#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "../Leibniz/leibniz.h"
#include "../File/file.h"
#include "./process.h"

void check_fork_error(pid_t pid)
{
	if (pid == -1) {
		perror("FORK: AN UNEXPECTED ERROR OCCURRED DURING THE FORK");
		exit(EXIT_FAILURE);
	}
}

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

	check_fork_error(pid);

	unsigned long mid = _MAX_ITERATIONS / 2;
	if (pid == 0) {
		long double partial_pi = leibniz_approx_pi(0, mid);

		FILE *file = open_file("./data/two_process/child.txt", "w");
		write_long_double(partial_pi, file);
		fclose(file);

		exit(EXIT_SUCCESS);
	}

	if (pid != 0) {
		long double partial_pi = leibniz_approx_pi(mid, _MAX_ITERATIONS);

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
	clock_t start = clock();
	pid_t pid;
	pid = fork();

	check_fork_error(pid);

	unsigned long factor = _MAX_ITERATIONS / 4;

	// Child
	if (pid == 0) {
		pid_t npid;
		npid = fork();

		check_fork_error(npid);

		// Nested child
		if (npid == 0) {
			long double partial_pi = leibniz_approx_pi(0, (1 * factor));

			FILE *file = open_file("./data/four_process/child_of_child.txt", "w");
			write_long_double(partial_pi, file);
			fclose(file);

			exit(EXIT_SUCCESS);
		}

		// Child
		if (npid != 0) {
			long double partial_pi = leibniz_approx_pi((1 * factor), (2 * factor));

			FILE *file = open_file("./data/four_process/child.txt", "w");
			write_long_double(partial_pi, file);
			fclose(file);

			wait(NULL); // wait - Nested child
		}

		exit(EXIT_SUCCESS);
	}

	// Father
	if (pid != 0) {
		pid_t npid;
		npid = fork();

		check_fork_error(npid);

		// Nested child
		if (npid == 0) {
			long double partial_pi = leibniz_approx_pi((2 * factor), (3 * factor));

			FILE *file = open_file("./data/four_process/child_of_father.txt", "w");
			write_long_double(partial_pi, file);
			fclose(file);

			exit(EXIT_SUCCESS);
		}

		// Father
		if (npid != 0) {
			long double partial_pi = leibniz_approx_pi((3 * factor), (4 * factor));

			FILE *file = open_file("./data/four_process/father.txt", "w");
			write_long_double(partial_pi, file);
			fclose(file);

			wait(NULL); // wait - nested child
		}

		wait(NULL); // wait - child
	}

	FILE *file = open_file("./data/four_process/child_of_child.txt", "r");
	long double p1 = read_long_double(file);
	fclose(file);

	file = open_file("./data/four_process/child.txt", "r");
	long double p2 = read_long_double(file);
	fclose(file);

	file = open_file("./data/four_process/child_of_father.txt", "r");
	long double p3 = read_long_double(file);
	fclose(file);

	file = open_file("./data/four_process/father.txt", "r");
	long double p4 = read_long_double(file);
	fclose(file);

	printf("PI: %.20Lf", p1 + p2 + p3 + p4);
	clock_t end = clock();

	return execution_time(start, end);
}
