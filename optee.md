
## OPTEE
https://github.com/OP-TEE  

## Build:
### QEMU ARM V7 (no BL31)
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

### QEMU ARM V8
$ sudo apt install python3-pyelftools  
$ sudo apt-get install build-essential python3-dev  
$ pip install pycryptodomex  

#### ubuntu 18
 install https://gitlab.freedesktop.org/slirp/libslirp
 1. download release 4.2.0
 2. meson build
 3. sudo ninja -C build install
 
$ repo init -u https://github.com/OP-TEE/manifest.git -m qemu_v8.xml -b master  
$ repo sync  
$ cd build  
$ make toolchains -j3  
$ make all run  
$ make -f qemu_v8.mk run-only  
(qemu) c

#### rebuild ATF.
$ make arm-tf DEBUG=1

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

ARMv8处理器包括一共4个运行级别， 其中EL3运行级将一个物理处理器分割为两个逻辑处理器，在Rich侧，有EL0/EL1/EL2三个运行级别分别对应一个操作系统的用户态，内核态，虚拟化态。 而在Trusted侧，只有EL0/EL1两个运行级别，对应的操作系统的用户态和内核态，所以在ARM处理器的Trust侧并不支持硬件虚拟化。
而在Rich和Trust之间切换需要ARM处理器的硬件指令SMC触发硬件异常，其会使系统从 EL1切换到EL3运行级由运行在EL3中的optee开源Secure Monitor的代码保存当前侧的硬件上下文，然后切换另一侧的缓存上下文到硬件寄存器中从而完成Rich和Trust之间的切换，其逻辑就像一个单纯的内核线程上下文切换。
所以要使用一个完整的带TrustZone支持的Linux，你需要在Linux侧有驱动程序发出SMC指令从而切换到Trust侧的OS，而在Trust侧的OS处理完成之后同样需要通过SMC（驱动或者系统调用）指令切换回Rich侧的Linux。

```cpp
/**
 * __arm_smccc_smc() - make SMC calls
 * @a0-a7: arguments passed in registers 0 to 7
 * @res: result values from registers 0 to 3
 * @quirk: points to an arm_smccc_quirk, or NULL when no quirks are required.
 *
 * This function is used to make SMC calls following SMC Calling Convention.
 * The content of the supplied param are copied to registers 0 to 7 prior
 * to the SMC instruction. The return values are updated with the content
 * from register 0 to 3 on return from the SMC instruction.  An optional
 * quirk structure provides vendor specific behavior.
 */
asmlinkage void __arm_smccc_smc(unsigned long a0, unsigned long a1,
			unsigned long a2, unsigned long a3, unsigned long a4,
			unsigned long a5, unsigned long a6, unsigned long a7,
			struct arm_smccc_res *res, struct arm_smccc_quirk *quirk);

/**
 * __arm_smccc_hvc() - make HVC calls
 * @a0-a7: arguments passed in registers 0 to 7
 * @res: result values from registers 0 to 3
 * @quirk: points to an arm_smccc_quirk, or NULL when no quirks are required.
 *
 * This function is used to make HVC calls following SMC Calling
 * Convention.  The content of the supplied param are copied to registers 0
 * to 7 prior to the HVC instruction. The return values are updated with
 * the content from register 0 to 3 on return from the HVC instruction.  An
 * optional quirk structure provides vendor specific behavior.
 */
asmlinkage void __arm_smccc_hvc(unsigned long a0, unsigned long a1,
			unsigned long a2, unsigned long a3, unsigned long a4,
			unsigned long a5, unsigned long a6, unsigned long a7,
			struct arm_smccc_res *res, struct arm_smccc_quirk *quirk);
```

 The scheme is something like:
Linux schedules in a Linux thread.
A timer interrupt occurs: from the irq handler of Linux, Linux can schedule out the active thread and schedule in another thread.
Later on, Linux can schedule back the former Linux thread , on the same cpu or on another cpu.
When using an optee, the same happens. For each non secure interrupt trapped while TEE is executing, TEE suspends the execution, invokes back the REE into the REE caller Linux thread which is simply asked to return back to TEE: 
https://github.com/linaro-swg/linux/blob/optee/drivers/tee/optee/rpc.c#L423. 
If the REE handling of the interrupt schedules out the active Linux thread, 
then TEE must wait Linux to schedule back the previously active Linux thread so that REE returns to TEE and resume the TEE thread execution.


### SMC Fast Call and Yielding Call
• Fast Calls execute atomic operations. The call appears to be atomic from the perspective of the calling
PE, and returns when the requested operation has completed.  
• Yielding Calls start operations that can be pre-empted by a Non-secure interrupt. The call can return
before the requested operation has completed. Appendix A: Example implementation of Yielding Service
calls provides an example of handling Yielding Calls.  

### Login Method
This depends on the login method.
TEE_LOGIN_PUBLIC: no UUID.  
TEE_LOGIN_USER: UUID is set by Linux kernel tee driver from effective user ID.  
TEE_LOGIN_GROUP: UUID is set by the CA and verified by Linux kernel tee driver against the groups the user belongs to.  
TEE_LOGIN_APPLICATION/TEE_LOGIN_APPLICATION_USER/TEE_LOGIN_APPLICATION_GROUP: not supported by OP-TEE.  
TEE_LOGIN_TRUSTED_APP: set by OP-TEE core from effective client TA UUID.  
TEE_LOGIN_REE_KERNEL (OP-TEE extension): no UUID.  
https://github.com/OP-TEE/optee_os/issues/6444  
