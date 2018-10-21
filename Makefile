
本机编译
```cpp
obj-m = hello.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
```

toolchain 编译：


$(CC)
$(LD)
CFLAGS
KBUILD_EXTRA_SYMBOLS=Modules.sysvers
obj-m := $(MODULE_NAME).o

make -C $(LINUX) M=$(PWD) modules
