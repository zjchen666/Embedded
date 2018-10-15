## IPC communication
  - file
  - share memory
  - pipe
  - semaphore
  - messageQueue
  - socket
   
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

### break point

为了在被追踪进程的某些目标地址设置一个断点，调试器会做如下工作：

 - 记住存储在目标地址的数据
 - 用 int 指令替换掉目标地址的第一个字节
 - 然后，当调试器要求 OS 运行该进程的时候，进程就会运行起来直到遇到 int 3，此处进程会停止运行，并且 OS 会发送一个信号(SIGTRAP)给调试器。调试器会收到一个信号表明其子进程（或者说被追踪进程）停止了。调试器可以做以下工作：
  - 在目标地址，用原来的正常执行指令替换掉 int 3 指令
  - 将被追踪进程的指令指针回退一步。这是因为现在指令指针位于刚刚执行过的 int 3 之后。
  - 允许用户以某些方式与进程交互，因为该进程仍然停止在特定的目标地址。这里你的调试器可以让你取得变量值，调用栈等等。
  - 当用户想继续运行，调试器会小心地把断点放回目标地址去（因为它在第 1 步时被移走了），除非用户要求取消该断点。
