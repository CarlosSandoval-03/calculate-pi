#include <stdio.h>
#include <stdlib.h>
#include "./Process/process.h"

int main(int argc, char **argv)
{
	printf("START\n");
	run_two_process();
	printf("\nEND\n");
	return EXIT_SUCCESS;
}
