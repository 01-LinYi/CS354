#include <xinu.h>

void delphiz(void)
{
    intmask mask;
    mask = disable();
    
    XINUTEST_PRINT("Welcome to Delphi\n");
    
    // Get the stack information
    uint32 ebp_val;
    __asm__ __volatile__("movl %%ebp, %0" : "=r" (ebp_val));
    uint32 *curr_ebp = (uint32 *)ebp_val;
    
    // We need to modify our return address to point to needarest's code after sleepms
    // Instead of trying to guess where the while loop is, let's reconstruct the 
    // call stack to return to needarest()
    
    // Step 1: Identify the stack frames
    uint32 *delphiz_ebp = curr_ebp;  // Current frame (delphiz)
    uint32 *sleepms_ebp = (uint32 *)*delphiz_ebp;  // Parent frame (sleepms)
    uint32 *needarest_ebp = (uint32 *)*sleepms_ebp;  // Grandparent frame (needarest)
    
    // Step 2: Get the return address from sleepms back to needarest
    uint32 sleepms_ret_addr = sleepms_ebp[1];
    
    // Step 3: Modify delphiz's return address to point to needarest's code after sleepms
    // This will make delphiz return directly to needarest, skipping any remaining code in sleepms
    delphiz_ebp[1] = sleepms_ret_addr;
        
    restore(mask);
    
    // Now when we return, we should go directly to needarest's code after sleepms
    // This should be the beginning of the while loop
}