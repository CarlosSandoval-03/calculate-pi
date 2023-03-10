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
	char *path_array[] = { "./data/two_process/child.txt", "./data/two_process/father.txt" };
	clock_t start = clock();
	pid_t pid;
	pid = fork();
	check_fork_error(pid);

	unsigned long middle = _MAX_ITERATIONS / 2;
	if (pid == 0) {
		long double partial_pi = leibniz_approx_pi(0, middle);
		write_partial_pi(path_array[0], partial_pi);
		exit(EXIT_SUCCESS);
	}

	if (pid != 0) {
		long double partial_pi = leibniz_approx_pi(middle, _MAX_ITERATIONS);
		write_partial_pi(path_array[1], partial_pi);
		wait(NULL);
	}

	long double pi = read_partials_pi(path_array, 2);
	printf("PI: %.20Lf", pi);
	clock_t end = clock();

	return execution_time(start, end);
}

double run_four_process()
{
	char *path_array[] = { "./data/four_process/child_of_child.txt", "./data/four_process/child.txt",
												 "./data/four_process/child_of_father.txt", "./data/four_process/father.txt" };
	clock_t start = clock();
	pid_t pid;
	pid = fork();
	check_fork_error(pid);

	unsigned long factor = _MAX_ITERATIONS / 4;
	if (pid == 0) {
		pid_t npid;
		npid = fork();
		check_fork_error(npid);

		// Nested child
		if (npid == 0) {
			long double partial_pi = leibniz_approx_pi(0, (1 * factor));
			write_partial_pi(path_array[0], partial_pi);
			exit(EXIT_SUCCESS);
		}

		// Child
		if (npid != 0) {
			long double partial_pi = leibniz_approx_pi((1 * factor), (2 * factor));
			write_partial_pi(path_array[1], partial_pi);
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
			write_partial_pi(path_array[2], partial_pi);
			exit(EXIT_SUCCESS);
		}

		// Father
		if (npid != 0) {
			long double partial_pi = leibniz_approx_pi((3 * factor), (4 * factor));
			write_partial_pi(path_array[3], partial_pi);
			wait(NULL); // wait - nested child
		}

		wait(NULL); // wait - child
	}

	long double pi = read_partials_pi(path_array, 4);
	printf("PI: %.20Lf", pi);
	clock_t end = clock();

	return execution_time(start, end);
}
