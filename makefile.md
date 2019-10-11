## $@ $< $^
$@ is the name of the file being generated,
and $< the first prerequisite (usually the source file). You can find a list of all these special variables in the GNU Make manual.

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
