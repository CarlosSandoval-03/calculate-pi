#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define _MAX_ITERATIONS 1e09

typedef struct {
	unsigned long start;
	unsigned long end;

	long double partial_pi;
} params_t;

void *leibniz_approx_pi(void *params_ptr)
{
	params_t *params = (params_t *)params_ptr;

	if (params->start > params->end) {
		perror("LEIBNIZ: INVALID RANGE");
		exit(EXIT_FAILURE);
	}

	long double x = 0.0;
	for (unsigned long i = (params->start); i < (params->end); i++) {
		x += pow(-1, i) / (2 * i + 1);
	}
	x *= 4;

	params->partial_pi = x;
	return NULL;
}

void calculate_pi_threads(int num_threads)
{
	pthread_t threads[num_threads];
	params_t params[num_threads];
	int r, *rh0;

	// Init params
	unsigned long factor = _MAX_ITERATIONS / ((unsigned long)num_threads);
	for (int i = 0; i < num_threads; i++) {
		params_t param;
		param.start = ((unsigned long)i) * factor;
		param.end = ((unsigned long)i + 1) * factor;
		param.partial_pi = 0;

		params[i] = param;
	}

	// Create threads
	int k = 0;
	for (int i = 0; i < num_threads; i++) {
		r = pthread_create(&threads[i], NULL, leibniz_approx_pi, (void *)&params[i]);
		if (r != 0) {
			perror("\nTHREAD ERROR: pthread_create error\n");
			exit(EXIT_FAILURE);
		}
		k++;
	}

	// Join threads
	for (int i = 0; i < num_threads; i++) {
		r = pthread_join(threads[i], (void **)&rh0);
		if (r != 0) {
			perror("\nTHREAD ERROR: pthread_join error\n");
			exit(EXIT_FAILURE);
		}
	}

	// Sum all
	long double pi = 0;
	for (int i = 0; i < num_threads; i++) {
		pi += (params[i]).partial_pi;
	}

	printf("Pi: %.20Lf\n", pi);
}

double run_n_threads(int num_threads)
{
	clock_t start = clock();
	calculate_pi_threads(num_threads);
	clock_t end = clock();

	return (double)(end - start) / CLOCKS_PER_SEC;
}

int main()
{
	int n_threads[] = { 1, 2, 4, 8, 16 };

	for (int i = 0; i < 5; i++) {
		double time = run_n_threads(n_threads[i]);
		printf("With %d thread(s), the execution time is: %f\n", n_threads[i], time);
	}

	return EXIT_SUCCESS;
}
