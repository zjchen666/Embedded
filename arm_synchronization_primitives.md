### Load, store conditional
__LDREX:__   
loads a word from memory, initializing the state of the exclusive
monitor(s) to track the synchronization operation. 
__STREX:__   
 Performs a conditional store of a word to memory. 
```cpp
   if no update between now and ldrex {
       set value;
       return 0
   } else {
       return 1;
   } 
```
__CLREX:__ When an operating system performs a context switch, it must reset the local monitor 

local monitor - per CPU
global monitor - Bus

__WFE:__  
The wake-up events for WFE are:  
• the execution of an SEV instruction on any processor in a multi-core system  
• an interrupt, unless masked  
• an asynchronous abort, for example a buffered write generating an access fault  
• a debug event, when invasive debug is enabled and permitted in the current state.  
  
__DMB:__  
• between acquiring a resource, for example through locking a mutex or
decrementing a semaphore, and making any access to that resource.  
• before making a resource available, for example through unlocking a mutex or
incrementing a semaphore.  

__Why do we need DMB after lock and before release lock?__  
You will note the Data Memory Barrier (DMB) instruction that is issued once the lock has been acquired.   
The DMB guarantees that all memory accesses before the memory barrier will be observed by all of the other CPUs in the 
system before all memory accesses made after the memory barrier.   
This makes more sense if you consider that once a lock has been acquired, a program will then access the data structure(s) 
locked by the lock The DMB in the lock function above ensures that accesses to the locked data structure are observed after 
accesses to the lock.

```cpp
locked EQU 1
unlocked EQU 0
; lock_mutex
; Declare for use from C as extern void lock_mutex(void * mutex);
EXPORT lock_mutex
lock_mutex PROC
LDR r1, =locked
1 LDREX r2, [r0]
CMP r2, r1 ; Test if mutex is locked or unlocked
BEQ %f2 ; If locked - wait for it to be released, from 2
STREXNE r2, r1, [r0] ; Not locked, attempt to lock it
CMPNE r2, #1 ; Check if Store-Exclusive failed
BEQ %b1 ; Failed - retry from 1
ARM Synchronization Primitives
DHT0008A Copyright © 2009 ARM. All rights reserved. 1-13
ID081709 Non-Confidential, Unrestricted Access
; Lock acquired
DMB ; Required before accessing protected resource
BX lr
2 ; Take appropriate action while waiting for mutex to become unlocked
WAIT_FOR_UPDATE
B %b1 ; Retry from 1
ENDP
; unlock_mutex
; Declare for use from C as extern void unlock_mutex(void * mutex);
EXPORT unlock_mutex
unlock_mutex PROC
LDR r1, =unlocked
DMB ; Required before releasing protected resource
STR r1, [r0] ; Unlock mutex
SIGNAL_UPDATE
BX lr
ENDP
```
