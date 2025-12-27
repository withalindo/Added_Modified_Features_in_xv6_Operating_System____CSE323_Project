// File: kernel/hapinfo.h (Ensure this matches user/hapinfo.h)

#ifndef _KERNEL_HAPINFO_H_
#define _KERNEL_HAPINFO_H_

#include "types.h"

#define HAPLOG_SIZE 16

// The structure containing the log data for a single sbrk call
struct haplog {
    // Used in sysproc.c
    uint64 old_sz;      // Process size before sbrk
    int sbrk_size;      // The 'n' argument passed to sbrk (positive or negative)
    
    // Used in proc.c (for sys_hapinfo/heap size change/time tracking)
    int size_change;    // The actual change in size (may differ from sbrk_size if lazy/eager)
    uint64 ticks;       // Clock ticks when the sbrk was called
};

// The structure passed to user space by sys_hapinfo
struct hapinfo {
    struct haplog log[HAPLOG_SIZE];
    int log_index;
};

#endif // _KERNEL_HAPINFO_H_
