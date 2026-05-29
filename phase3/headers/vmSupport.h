#ifndef VM_SUPPORT
#define VM_SUPPORT

#include "../../headers/types.h"
#include "../../headers/klog.h"
#include "./functions.h"
#include "./const.h"
#include <uriscv/cpu.h>
#include <uriscv/liburiscv.h>
#include <uriscv/arch.h>

extern swap_t swap_pool[POOLSIZE];
extern int swapPoolSemaphore;
static int frameIndex;

void pager();
int pageReplacement();

#endif
