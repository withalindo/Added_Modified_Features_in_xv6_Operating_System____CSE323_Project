#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "kernel/param.h" // Needed for NPROC (max processes)

struct pstat {
  int inuse[NPROC];   // 1 if this slot is in use, 0 otherwise
  int pid[NPROC];     // The Process ID
  int state[NPROC];   // The process state (e.g., RUNNING, SLEEPING)
  int ticks[NPROC];   // Total CPU ticks consumed
  int waittime[NPROC];// Ticks spent in RUNNABLE state
  int scheduled[NPROC]; // Number of times scheduled
  int tickets[NPROC]; // Tickets (default 1)
};
#endif // _PSTAT_H_