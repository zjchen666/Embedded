## _$@ $< $^_
```
$@ is the name of the file being generated,
and $< the first prerequisite (usually the source file). You can find a list of all these special variables in the GNU Make manual.
```
For example, consider the following declaration:

```cpp
all: library.cpp main.cpp
```
In this case:

$@ evaluates to all  
$< evaluates to library.cpp  
$^ evaluates to library.cpp main. 


## 如何用不同的CFLAGS使用Makefile编译不同的c文件？  

尝试使用目标特定的变量。目标特定变量声明如下：
TARGET: VAR := foo  # Any valid form of assignment may be used ( =, :=, +=, ?=)
现在，当命名为TARGET的目标正在进行时，名为VAR的变量将具有值“foo”。

使用目标特定的变量，你可以这样做，例如：

```cpp
OBJ=[all other .o files here, e.g. D.o, D.o, E.o .... Z.o]
SPECIAL_OBJS=A.o B.o

all: $(OBJ) $(SPECIAL_OBJS)

$(SPECIAL_OBJS): EXTRA_FLAGS := -std=c99   # Whatever extra flags you need

%.o: %.c
     @echo [Compiling]: $<
     $(CC) $(CFLAGS) $(EXTRA_FLAGS) -o $@ -c $<
```

## source code in different folders
```
VPATH += dir1 dir2 ...
```


= 是最基本的赋值   
:= 是覆盖之前的值   
?= 是如果没有被赋值过就赋予等号后面的值   
+= 是添加等号后面的值 . 


makefile中":="和“=”的区别 .   
在makefile中，经常能看到这种赋值方式：    
MyNumber := 123 .     
这种方式洋名叫做expansion assignment， 翻译过来叫扩展赋值, 我一般就叫冒号等号。这位同学就问了，那么它和普通的等号有啥不一样捏？咱们废话少说，直接看代码。   
ANIMAL = FROG .   
VAR = "$(ANIMAL) DOG CAT" .   
ANIMAL = TIGER

test: 
echo $(VAR)
输出是：
    TIGER DOG CAT
再来看冒号等号的输出和上面有啥不一样：
ANIMAL := FROG
VAR := "$(ANIMAL) DOG CAT"
ANIMAL := TIGER
test：
    echo $(VAR)
输出时：
    FROG DOG CAT
看出来哪里不一样了吗？
没错，直接使用"="，变量在调用的时候一起展开，也就是在执行"echo $(VAR)"的时候；但是使用":="的时候，变量在赋值的时候就展开了。

makefile下$^,$@,$?,$&lt;,$(@D),$(@F)定义使用详解
变量定义：  
$^
所有的依赖目标的集合。以空格分隔。如果在依赖目标中有多个重复的，那个这个变量
会去除重复的依赖目标，只保留一份。
   
$@ . 
表示规则中的目标文件集。在模式规则中，如果有多个目标，那么，"$@"就是匹配于
目标中模式定义的集合
    
$?  
所有比目标新的依赖目标的集合。以空格分隔。
    
$<
依赖目标中的第一个目标名字。如果依赖目标是以模式（即"%"）定义的，那么"$<"将
是符合模式的一系列的文件集。注意，其是一个一个取出来的。
   
$(@D)
表示"$@"的目录部分（不以斜杠作为结尾） ，如果"$@"值是"dir/foo.o"，那么"$(@D)"就
是"dir"，而如果"$@"中没有包含斜杠的话，其值就是"."（当前目录） 。
     
 $(@F)
表示"$@"的文件部分，如果"$@"值是"dir/foo.o"，那么"$(@F)"就是"foo.o"，"$(@F)"相
当于函数"$(notdir $@)"
 
举例详解：
有main.c  test.c  test1.c  test2.c 四个源文件
 
例子1：
%.o : %.c
gcc  -c  $<  -o  $@
 
把所以的c文件编译生成对应的o文件，$<代表每次取的c文件，$@代表每次c文件对应的目标文件
 
 
例子2：
main ： main.o  test.o  test1.o  test2.o
gcc  -o  $@  $^
把所有的o文件编译生成可执行的main文件，$^代表所以的依赖文件集合（main.o  test.o  test1.o  test2.o），@代表目标文件（main）
 
例子3：
lib : test.o  test1.o  test2.o
ar r lib $?
 
把有更新的依赖文件重新打包到库lib中， 如果只有test1.o更新，则$?代表test1.o， 如果test.o  test1.o都有更新，则$?代表test.o  test1.o的集合。
 
总结：
 
$^      所有依赖目标的集合
$?      所有有更新的依赖目标集合
$<      依赖目标中的第一个目标，如果依赖以（%）模式定义，则一个一个取出来的
$@     目标文件
$(@D)   $@的目录部分
$(@F)   $@的文件部分
 
记忆方法：
 
dst：source1.o  source2.o  source3.o  source4.o  
xx ......
 
$^    其中^表示水平的范围限定，包含所有的依赖文件集合（source1.o  source2.o  source3.o  source4.o ）
$?    其中?表示哪些依赖文件有更新是未知的，有更新的依赖文件集合（?）
$<    其中<表示从集合中取值，第一个依赖的文件 （source1.o）
$@   目标文件  （dst）
$(@D)   $@的目录部分
$(@F)   $@的文件部分


@ + shell command

1、如果makefile执行的命令前面加了@符号，则不显示命令本身而只显示结果。 
2、通常make执行的命令出错（该命令的退出状态非0）就立刻终止，不再执行后续命令，但是如果命令前面加上“-”，即使这条命令出错，makefile也会继续执行后续命令的。
