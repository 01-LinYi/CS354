#include <xinu.h>

void myuserret(void)
{
    kprintf("In myuserret()\n");
    while(1) {}
}