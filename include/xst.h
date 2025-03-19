#ifndef _XST_H_
#define _XST_H_

struct xst
{
    uint16 xstslpret;   // New priority for I/O-bound processes
    uint16 xstqexp;     // New priority for CPU-bound processes
    uint16 xstquantum;  // Time slice (in msec) for this priority level
};

#endif