#ifndef SPIN_H
#define SPIN_H
typedef int SPINLOCK;

extern void SpinAcquire(SPINLOCK lock);
extern void SpinRelease(SPINLOCK lock);
#endif
