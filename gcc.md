### 自定义段:  
在 gcc 编译出来的目标文件中，代码一般是放到 .text 段，全局变量和静态变量被放到 .data 和 .bss 段。这只是默认行为，我们有时可能希望变量或某些代码放在一个自定义的段中去以实现某些特定功能，比如为了满足某些硬件的内存和 I/O 地址布局，或者像 Linux 内核中用来完成一些初始化和用户控件复制时出现的错误异常等。
GCC 提供了一个扩展机制，
1. 使得我们可以将变量放在我们自定义的段中。
```cpp

__attribute__((section("myvarsection"))) int global_var = 18;
 
__attribute__((section("myfuncsection"))) void hello(void);
 
void hello(void)
{
        printf ("hello world\n");
 
        printf ("my global_var:%d\n", global_var);
 
}
```
2.还可以直接用objcopy update section来替换.  

objcopy -> ELF file -> Bin file    
objdump - disassemble -> dump file   
ld -> Map file   
ld -> ELF file  
readelf - get ELF file details  
nm -> symblo information  
addr2line + elf file - get source code position   
