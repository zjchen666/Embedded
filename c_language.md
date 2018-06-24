
### volatile

volatile 告诉编译器i是随时可能发生变化的，每次使用它的时候必须从i的地址中读取，因而编译器生成的可执行码会重新从i的地址读取数据放在k中。 
而优化做法是，由于编译器发现两次从i读数据的代码之间的代码没有对i进行过操作，它会自动把上次读的数据放在k中。而不是重新从i里面读。这样以来，如果i是一个寄存器变量或者表示一个端口数据就容易出错，所以说volatile可以保证对特殊地址的稳定访问，不会出错。 
1) 并行设备的硬件寄存器（如：状态寄存器） 
2) 一个中断服务子程序中会访问到的非自动变量(Non-automatic variables) 
3) 多线程应用中被几个任务共享的变量   

__避免被 Cache!!!__

### 二维数组：
数组指针 - int (*p)[10]

指针数组 - int* p[10]

int a[3][3] = {1,2,3,4,5,6,7,8,9}
二维数组指针是行指针： 访问元素 *(*(a + 1) + 1)

### constant

const int a; - a为 constant int  
int const a; - 同上   
const int *a; - 指针的值为 constant   
int * const a; - 指针 constant  
int const * a const; - 指针和值都为constant  
