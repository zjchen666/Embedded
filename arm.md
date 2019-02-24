## ARMv8 exception level、excution state、secure level 

### exception level
- EL0 - Application
- EL1 - OS kernel
- EL2 - Hypervisor, Doesn't have secure mode
- EL3 - Secure monitor, secure state only

当接收到一个异常时，异常级别只能调高或保持  
当从异常返回时，异常级别只能调低或保持  
异常相关术语
术语

说明

Taking an exception：  
PE第一次回应一个异常，此时PE state称为taken from, 之后PE状态为taken to  
Returning from exception  

当异常返回指令被提交运行，PE state就是return from exception  
异常级别  
不同异常级别，异常的优先级不同如EL3的异常高于EL1的异常  
  
精准异常  
找到某条指令，这条指令前的所有指令都执行完毕，这条指令之后的所有指令都未执行（执行的需要回退），这样PE状态就被记录下载，异常处理完成后就可以恢复。除了SError irq之外，其它的都是精准异常

同步异常  
（1）异常的产生是和cpu core执行的指令或者试图执行相关
（2）硬件提供给handler的返回地址就是产生异常的那一条指令所在的地址
（3）synchronous exception又可以细分成两个类别：
a). 一种我们称之为synchronous abort，例如未定义的指令、data abort、prefetch instruction abort、SP未对齐异常，debug exception等等;
b). 还有一种是正常指令执行造成的，包括SVC/HVC/SMC指令，这些指令的使命就是产生异常。

异步异常  
asynchronous exception基本上可以类似大家平常说的中断，它是毫无预警的，丝毫不考虑cpu core感受的外部事件（需要注意的是：外部并不是表示外设，这里的外部是针对cpu core而言，有些中断是来自SOC的其他HW block，例如GIC，这时候，对于processor或者cpu（指soc）而言，这些事件是内部的），这些事件打断了cpu core对当前软件的执行，因此称之interrupt。interrupt或者说asynchronous exception有下面的特点：
（1）异常和CPU执行的指令无关。  
（2）返回地址是硬件保存下来并提供给handler，以便进行异常返回现场的处理。这个返回地址并非产生异常时的指令  
根据这个定义IRQ、FIQ和SError interrupt属于asynchronous exception。  

SError interrupt  
SError interrupt是发生了external abort导致的异步异常（或称中断）。 
external abort来自memory system， 是访问外部memory system产生的异常(当然不是所有的来自memory system的abort都是external abort，例如来自MMU的abort就不是external abort，这里的external是针对processor而非cpu core而言，因此MMU实际上是internal的）。external abort发生在processor通过bus访问memory的时候（可能是直接对某个地址的读或者写，也可能是取指令导致的memory access），processor在bus上发起一次transaction，在这个过程中发生了abort，abort来自processor之外的memory block、device block或者interconnection block，用来告知processor，搞不定了，你自己看着办吧。external abort可以被实现成synchronous exception（precise exception），也可以实现成asynchronous exception（imprecise exception）。如果external abort是asynchronous的，那么它可以通过SError interrupt来通知cpu core  


### excution state  

- __AArch32__

提供13个32bit通用寄存器R0-R12，一个32bit PC指针 (R15)、堆栈指针SP (R13)、链接寄存器LR (R14)  
提供一个32bit异常链接寄存器ELR, 用于Hyp mode下的异常返回  
提供32个64bit SIMD向量和标量floating-point支持  
提供两个指令集A32（32bit）、T32（16/32bit）  
兼容ARMv7的异常模型，映射到ARMV8异常模型  
使用32bit虚拟地址  
使用CPSR来保存当前PE状态   
协处理器只支持CP10\CP11\CP14\CP15  

- __AArch64__  
提供31个64bit通用寄存器X0-X30（W0-W30），其中X30是程序链接寄存器LR   
提供一个64bit PC指针、堆栈指针SPx 、异常链接寄存器ELRx  
提供32个128bit SIMD向量和标量floating-point支持  
定义ARMv8异常等级ELx（x<4）,x越大等级越高，权限越大   
提供64bit虚拟地址  
定义一组PE state寄存器SPSR_ELx来保存 PSTATE（NZCV/DAIF/CurrentEL/SPSel等），用于保存PE当前的状态信息  
没有协处理器概念，系统寄存器带后缀n标志最低的异常访问级别  

https://www.cnblogs.com/smartjourneys/p/6845078.html
