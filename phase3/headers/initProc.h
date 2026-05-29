#ifndef INIT_PROC
#define INIT_PROC

#include "../../headers/types.h"
#include "../../headers/klog.h"
#include <uriscv/cpu.h>
#include <uriscv/liburiscv.h>

swap_t swap_pool[POOLSIZE];
int swapPoolSemaphore;

void test();

#endif
