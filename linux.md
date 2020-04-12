## Process：
## 进程和线程 ##
   1. 都是control block task_struct
   2. 调度的都是task_struct(都是线程调度)
   3. Fork：子进程复制所有父进程的task_struct. 并把memory置成read only。copy-on-write 写时触发page fault 异常。分配内存。谁写谁分配。
   4. vfork： 没有MMU的系统， 内存部分共享。
   5. pthread_create 也是clone一个 task struct并共享所有资源。
   6. 每个线程有独自的pid（top -H）， 一个进程共享一个tpid。

### priority and nice
   1. RT thread。pri比较好理解，即进程的优先级，pri越小，优先级越高。0 - 99
   2. nornal thread 那nice值呢？nice表示进程可被执行的优先级的修正数值。如前面说的，pri越小越优先被执行，那么加入nice之后pri(new)=pri(old)+nice。这样,当nice为负值的时候，该程序的pri变小，优先级越高。 -19 - 20. 
 _nice与renice_
   1.nice的作用是启动时设置nice的值  
   2.renice的作用是修改已经存在的进程的nice值

## Memory 
https://zhuanlan.zhihu.com/p/34715622
