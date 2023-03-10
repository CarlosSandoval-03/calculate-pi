#pragma once
#ifndef _PROCESS_H_
#define _PROCESS_H_

#define _MAX_ITERATIONS 1e09

#include <time.h>

double execution_time(clock_t start, clock_t end);
double run_one_process();
double run_two_process();
double run_four_process();

#endif // _PROCESS_H_
