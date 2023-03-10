#pragma once
#ifndef _PROCESS_H_
#define _PROCESS_H_

#define _MAX_ITERATIONS 1e09

#include <time.h>

double execution_time(clock_t start, clock_t end);
void run_two_process();

#endif // _PROCESS_H_
