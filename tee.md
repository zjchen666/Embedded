
## OPTEE
https://github.com/OP-TEE  

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

###  Secure Monitor Call (SMC) and Hypervisor Call (HVC)

EL0 - The lowest Exception level. The Exception level that is used to execute user applications,
in Non-secure state.  
EL1 - Privileged Exception level. The Exception level that is used to execute operating
systems, in Non-secure state.  
EL2 - Hypervisor Exception level. The Exception level that is used to execute hypervisor code.
EL2 is always in Non-secure state.  
EL3 - Secure Monitor Exception level. The Exception level that is used to execute Secure
Monitor code, which handles the transitions between Non-secure and Secure states. EL3
is always in Secure state.  
