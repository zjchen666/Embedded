### How to build AOSP

## Setup for AOSP development Env and Download the AOSP code:
https://source.android.com/docs/setup/start/requirements

## Build
### install hikey vendor package
```
$ ./device/linaro/hikey/fetch-vendor-package.sh
```

### Build target and build type
```
$ list_products
$ lunch hikey960_tv-ap4a-eng

$ repo init -u https://android.googlesource.com/platform/manifest -b main
$ repo sync -j`nproc`
$ ./device/linaro/hikey/fetch-vendor-package.sh
$ source build/envsetup.sh
$ lunch hikey960-trunk_staging-userdebug
$ make -j`nproc`

// can't find python2 issue
1. $ vim ./vendor/linaro/hikey960/20240817/bootloader/mkdtimg
2. $ change /usr/bin/env python2 to /usr/bin/python2
```
