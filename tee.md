
## OPTEE
### QEMU 
https://www.op-tee.org/docs/qemu/  
Ubuntu 18.04

$ sudo apt-get install android-tools-adb android-tools-fastboot autoconf \
	automake bc bison build-essential cscope curl device-tree-compiler flex \
	ftp-upload gdisk iasl libattr1-dev libc6:i386 libcap-dev libfdt-dev \
	libftdi-dev libglib2.0-dev libhidapi-dev libncurses5-dev \
	libpixman-1-dev libssl-dev libstdc++6:i386 libtool libz1:i386 make \
	mtools netcat python-crypto python-serial python-wand unzip uuid-dev \
	xdg-utils xterm xz-utils zlib1g-dev
  
$ mkdir optee-qemu && cd optee-qemu  
$ repo init -u https://github.com/OP-TEE/manifest.git -m default.xml -b master  
$ repo sync  
$ cd build  
$ make toolchains -j3  
$ make all run  
$ make -f qemu.mk run-only
(qemu) c
