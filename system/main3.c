#include <xinu.h>

#define TEST3a 0

extern void needarest(void);
extern void wrongturn175(pid32 traveler);
extern void wrongturn175a(pid32 traveler);


void main3(void)
{
    pid32 traveler_pid;
    pid32 modifier_pid;

    /* Create the traveler process with a lower priority than main3() */
    traveler_pid = create(needarest, INITSTK, INITPRIO-1, "traveler", 0);
    resume(traveler_pid);

    #if TEST3a
    /* Create a process to modify traveler's return address */
    modifier_pid = create(wrongturn175a, INITSTK, INITPRIO-1, "modifier", 1, traveler_pid);
    resume(modifier_pid);
    #endif
}
