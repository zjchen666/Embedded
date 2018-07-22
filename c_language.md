
### volatile

volatile 告诉编译器i是随时可能发生变化的，每次使用它的时候必须从i的地址中读取，因而编译器生成的可执行码会重新从i的地址读取数据放在k中。 
而优化做法是，由于编译器发现两次从i读数据的代码之间的代码没有对i进行过操作，它会自动把上次读的数据放在k中。而不是重新从i里面读。这样以来，如果i是一个寄存器变量或者表示一个端口数据就容易出错，所以说volatile可以保证对特殊地址的稳定访问，不会出错。 
1) 并行设备的硬件寄存器（如：状态寄存器） 
2) 一个中断服务子程序中会访问到的非自动变量(Non-automatic variables) 
3) 多线程应用中被几个任务共享的变量   

__避免被 Cache!!!__

### 指针：
数组指针 - int (*p)[10]
指针数组 - int* p[10]
函数指针 - int (*p)(int)
函数指针数组 - int (*p[])(int)

int a[3][3] = {1,2,3,4,5,6,7,8,9}
二维数组指针是数组指针类型： 访问元素 *(*(a + 1) + 1)

### constant

const int a; - a为 constant int  
int const a; - 同上   
const int *a; - 指针的值为 constant   
int * const a; - 指针 constant  
int const * a const; - 指针和值都为constant  

### 自动类型转换
表达式中存在有符号类型和无符号类型时所有的操作数都自动转换为无符号类型   
unsigned int a = 3;   
int b = -10;   
a + b > 0  
原因是b 转换为 uint  

面试题链接：
http://blog.jobbole.com/109117/
https://blog.csdn.net/sailor_8318/article/details/2215041
