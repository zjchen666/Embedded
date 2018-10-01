
## OPTEE
### QEMU 
https://www.op-tee.org/docs/qemu/

$ sudo apt-get install [pre-reqs]
$ mkdir optee-qemu && cd optee-qemu
$ repo init -u https://github.com/OP-TEE/manifest.git -m default.xml -b master
$ repo sync
$ cd build
$ make toolchains -j3
$ make all run
(qemu) c
