
###
### volatile

volatile 告诉编译器i是随时可能发生变化的，每次使用它的时候必须从i的地址中读取，因而编译器生成的可执行码会重新从i的地址读取数据放在k中。 
而优化做法是，由于编译器发现两次从i读数据的代码之间的代码没有对i进行过操作，它会自动把上次读的数据放在k中。而不是重新从i里面读。这样以来，如果i是一个寄存器变量或者表示一个端口数据就容易出错，所以说volatile可以保证对特殊地址的稳定访问，不会出错。 
1) 并行设备的硬件寄存器（如：状态寄存器） 
2) 一个中断服务子程序中会访问到的非自动变量(Non-automatic variables) 
3) 多线程应用中被几个任务共享的变量   

__避免被 Cache!!!__

### 指针：
-数组指针 - int (*p)[10]  
-指针数组 - int* p[10]  
-函数指针 - int (*p)(int)  
-函数指针数组 - int (*p[])(int)

int a[2][3] = {1,2,3,4,5,6,7,8,9} a type - int (int*)[2]
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

自动转换遵循以下规则：

1) 若参与运算量的类型不同，则先转换成同一类型，然后进行运算。

2) 转换按数据长度增加的方向进行，以保证精度不降低。如int型和long型运算时，先把int量转成long型后再进行运算。

     a.若两种类型的字节数不同，转换成字节数高的类型

     b.若两种类型的字节数相同，且一种有符号，一种无符号，则转换成无符号类型

3) 所有的浮点运算都是以双精度进行的，即使仅含float单精度量运算的表达式，也要先转换成double型，再作运算。

4) char型和short型参与运算时，必须先转换成int型。

5) 在赋值运算中，赋值号两边量的数据类型不同时，赋值号右边量的类型将转换为左边量的类型。如果右边量的数据类型长度左边长时，将丢失一部分数据，这样会降低精度，丢失的部分按四舍五入向前舍入。

面试题链接：
http://blog.jobbole.com/109117/
https://blog.csdn.net/sailor_8318/article/details/2215041

### 数据类型的长度

编译器可以根据自身硬件来选择合适的大小，但是需要满足约束：short和int型至少为16位，long型至少为32位，并且short型长度不能超过int型，而int型不能超过long型。这即是说各个类型的变量长度是由编译器来决定的，而当前主流的编译器中一般是32位机器和64位机器中int型都是4个字节（例如，GCC）。下面列举在GCC编译器下32位机器和64位机器各个类型变量所占字节数：

   | C类型	          | 32bit 	| 64bit |
   | -------------- |:--------:| -----:|
   | char	        |   1	    |  1    |
   | short          |   2	    |  2    |
   | uint     	     |   4	    |  4    |
   | int	           |   4	    |  4    |
   | long    	     |   4	    |  8    |
   | long long      |   8	    |  8    |
   | char*	        |   4	    |  8    |
   | float	        |   4	    |  4    |
   | double	        |   8	    |  8    |
   | size_t         |   4      |  8    |
   
需要说明一下的是指针类型存储的是所指向变量的地址，所以32位机器只需要32bit，而64位机器需要64bit。

为什么使用 size_t？
1. 保证可移植性. 32bit int - 4bytes, 64bit int - 4 bytes. size_t is aligned to address width.
2. if use uint long, 16 bit machine time complexicity is high.

### data alignment
```cpp
struct __attribute__((packed)) {
    char a, b, *c;
    int *d, e;
    short *f, g;
} test;
sizeof(test) : 20 bytes
w/o attribute packeted: sizeof(test) - 24 bytes

```
