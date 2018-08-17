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
 - trace buffer
 - valgrid
 - Set Magic Number.

## Memory Leak
 - valgrid
 - malloc_debug/free_debug
 - top
 - /proc/meminfo
 - free
 - vstate
 - buddyinfo

### Crash
user space: GDB + coredump
kernel space: kdump + crash
