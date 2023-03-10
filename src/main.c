#include <stdio.h>
#include <stdlib.h>
#include "./Process/process.h"

int main(int argc, char **argv)
{
	printf("START ONE PROCESS\n");
	double execution_time = run_one_process();
	printf("\nExecution time: %f secs\n", execution_time);

	printf("\n\nSTART TWO PROCESS\n");
	execution_time = run_two_process();
	printf("\nExecution time: %f secs\n", execution_time);

	printf("\n\nSTART FOUR PROCESS\n");
	execution_time = run_four_process();
	printf("\nExecution time: %f secs\n", execution_time);
	return EXIT_SUCCESS;
}
