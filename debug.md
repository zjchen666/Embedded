## Share Lib
   - compile: -shared -fpic
   - nm, objdump, readelf

## Memory Corruption
### Reason:
- Double Free -> segment fault
- buffer/heap/stack overflow.
- Not initialization
- Dangling Pointer.
- unaligned data structure

### How to debug:
 - GDB
 - core dump
 - assert()/abort()
 - back trace
 - converity
 - mtrace
   ```cpp
       1. In code add below:
       #include <mcheck.h>
        void mtrace(void);
        void muntrace(void);
       2. compile: gcc testmtrace.c -o testmtrace 
       3. run: ./testmtrace 
       4. analyize: mtrace testmtrace mytrace.log

   ```
 - trace buffer
 - valgrid
 - Set Magic Number.

## Memory Leak
 - valgrid
 - glibc MALLOC_CHECK //export MALLOC_CHECK_=2
 - malloc_debug/free_debug
 - top
 - /proc/meminfo
 - free
 - vstate
 - buddyinfo

### Crash
user space: GDB + coredump
kernel space: kdump + crash
