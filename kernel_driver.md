
## 字符设备驱动
```cpp
/* define module init and exit function */
module_init(driver_module_init_function);
module_exit(driver_module_exit_function);

/* register device. after that the drive is appeared in /proc/devices */
register_chrdrv_region(major_number, DEVICE_NAME, file_ops);
allocate_chrdrv_region()
unregister_chrdrv()

/* create device class */
register_class()

/*方法一： create device file node udev  */
device_create()

/*方法二： 使用 mknod 手动创建*/
```

## 内核同步：
抢占和非抢占内核， 如果内核不支持抢占， 几乎可以不用锁。
Kernel Preemptive
Kernel Non-Preemptive

- 单CPU 非抢占，自旋锁退化为NOP
- 单CPU 抢占，自旋锁会disable preemptive和中断，why？ ans：不能进行进程调度。否则会死锁 例如：A持有锁 schdule 到B，B访问锁。
- 多CPU和单CPU可抢占类似。
- 为什么要使用spinlock？ 
  spinlock不会睡眠（muxtex，semphore都会）， 如果一块 critical section 同时被ISR访问，要使用spinlock。
  
### spin Lock
```cpp
普通自旋锁：
    spin_lock_init()
    spin_lock()
    spin_try_lock()
    spin_unlock()
```

自旋锁上锁后只能被中断影响，thread中需使用带禁止中断的自旋锁， ISR中使用spin_lock/spin_unlock.
```cpp
    spin_lock_irq()
    spin_unlock_irq()
```
单核CPU/多核CPU 自旋锁使用区别？

### mutex
### semphore
  

## 中断
什么情况下中断需要使用自旋锁？

可屏蔽终断/不可屏蔽中断NMI
共享中断
中断上下文
request_irq()
free_irq()

中断处理机制：
tasklet, workqueue.
