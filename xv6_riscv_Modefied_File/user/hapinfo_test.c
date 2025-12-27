#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#include "user/hapinfo.h" // Now relying on the external header file

/*
 * NOTE: This program assumes the following structure definitions exist 
 * in your user/hapinfo.h and kernel/hapinfo.h files:
 * * #define HAPLOG_SIZE 16 // Or whatever size you defined
 * struct haplog {
 * uint old_sz;       // Old heap size before sbrk
 * int sbrk_size;     // Argument passed to sbrk (change in size)
 * };
 * struct hapinfo {
 * int log_index;     // Number of sbrk calls logged
 * struct haplog log[HAPLOG_SIZE];
 * };
 */

int main(void) {
    struct hapinfo hst;
    
    // CORRECTION: Removed file descriptor '1'
    printf("Making sbrk() calls to log heap activity...\n");

    // Perform several sbrk calls to log activity
    sbrk(1000);    // Grow
    sbrk(500);     // Grow more
    sbrk(-200);    // Shrink
    sbrk(300);     // Grow
    
    if (hapinfo(&hst) < 0) {
        // CORRECTION: Removed file descriptor '2'
        printf("hapinfo failed!\n");
        // CORRECTION: Added integer argument for exit status
        exit(1);
    }
    
    // CORRECTION: Removed file descriptor '1'
    printf("\n--- Heap Activity Log (hapinfo) ---\n");
    // CORRECTION: Removed file descriptor '1'
    printf("Total sbrk calls logged: %d\n", hst.log_index);
    // CORRECTION: Removed file descriptor '1'
    printf("Old Size\tSbrk Arg\tSize Change\tTicks\t\tNew Size\n");
    // CORRECTION: Removed file descriptor '1'
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < hst.log_index; i++) {
        // NOTE: Using all fields from the updated struct
        uint64 new_sz = hst.log[i].old_sz + hst.log[i].size_change;
        
        printf("%lu\t\t%d\t\t%d\t\t%lu\t\t%lu\n",
            hst.log[i].old_sz,
            hst.log[i].sbrk_size,
            hst.log[i].size_change,
            hst.log[i].ticks,
            new_sz);
    }
    
    // CORRECTION: Added integer argument for exit status
    exit(0);
}
