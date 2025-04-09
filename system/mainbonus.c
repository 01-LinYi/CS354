#include <xinu.h>

extern void needarest(void);
extern void wrongturn175z(pid32 traveler);


void mainbonus(void)
{
    pid32 traveler_pid;
    pid32 modifier_pid;

    // Create the traveler process with a lower priority
    traveler_pid = create(needarest, INITSTK, INITPRIO-1, "traveler", 0);
    resume(traveler_pid);

    // Give traveler time to enter sleepms()
    sleepms(300);

    // Create a process to modify traveler's return address
    modifier_pid = create(wrongturn175z, INITSTK, INITPRIO-1, "modifier", 1, traveler_pid);
    resume(modifier_pid);
}