#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
// #include "user/pstat.h" // Commenting out until we confirm 'user/pstat.h' exists and is complete

// Define the pstat structure locally for guaranteed compilation.
// NOTE: These field names (waittime, scheduled) must exactly match
// what you defined in your actual kernel's pstat structure.
#define NPROC 64
struct pstat {
  int inuse[NPROC];      // whether this slot of the process table is in use (1 or 0)
  int pid[NPROC];        // the PID of each process
  int state[NPROC];      // the state of each process
  uint ticks[NPROC];     // the number of total timer ticks this process has received
  int waittime[NPROC];   // the number of ticks this process spent waiting (matches user's print statement)
  int scheduled[NPROC];  // the number of ticks this process spent being scheduled (matches user's print statement)
  int tickets[NPROC];    // the number of tickets for this process
};

// State mapping for printing (based on standard xv6 state enum values)
static char *states[] = {
  [0]     "UNUSED",
  [1]     "EMBRYO",
  [2]     "SLEEPING",
  [3]     "RUNNABLE",
  [4]     "RUNNING",
  [5]     "ZOMBIE",
  [6]     "UNKNOWN_STATE" // Added to handle states not explicitly listed (e.g., if you have 6 states)
};

int main(void) {
    struct pstat pst;
    
    // CORRECTION: Removed file descriptor '1'
    printf("--- Pstat Test ---\n");
    
    // Create a child process to ensure multiple processes exist
    int pid = fork();
    if (pid == 0) {
        // Child: Spin briefly to accumulate metrics
        // CORRECTION: Removed file descriptor '1'
        printf("Child process (PID %d) spinning...\n", getpid());
        for (int i = 0; i < 50000; i++) {}
        
        // CORRECTION: Added integer argument for exit status
        exit(0); 

    } else if (pid > 0) {
        // CORRECTION: Added integer pointer argument (0 for simplicity)
        wait(0); // Parent waits for child
    }

    if (getpinfo(&pst) == 0) {
        // CORRECTION: Removed file descriptor '1'
        printf("PID\tSTATE\tTICKS\tWAIT\tSCHED\tTICKETS\n");
        for (int i = 0; i < NPROC; i++) {
            if (pst.inuse[i]) {
                // Determine the state string, using the local array
                char *state_str = "UNKNOWN";
                if (pst.state[i] >= 0 && pst.state[i] <= 6) {
                    state_str = states[pst.state[i]];
                }
                
                // CORRECTION: Removed file descriptor '1'
                printf("%d\t%s\t%d\t%d\t%d\t%d\n",
                    pst.pid[i],
                    state_str,
                    pst.ticks[i],
                    pst.waittime[i],
                    pst.scheduled[i],
                    pst.tickets[i]);
            }
        }
    } else {
        // CORRECTION: Removed file descriptor '2'
        printf("getpinfo failed!\n");
        
        // CORRECTION: Added integer argument for exit status
        exit(1);
    }

    // CORRECTION: Added integer argument for exit status
    exit(0);
}