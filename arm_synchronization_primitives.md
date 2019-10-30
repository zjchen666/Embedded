LDREX
STREX


__Why do we need DMB after lock and before release lock?__  
You will note the Data Memory Barrier (DMB) instruction that is issued once the lock has been acquired.   
The DMB guarantees that all memory accesses before the memory barrier will be observed by all of the other CPUs in the 
system before all memory accesses made after the memory barrier.   
This makes more sense if you consider that once a lock has been acquired, a program will then access the data structure(s) 
locked by the lock The DMB in the lock function above ensures that accesses to the locked data structure are observed after 
accesses to the lock.
