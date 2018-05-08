## kernel driver ##
```cpp
/* define module init and exit function */
module_init(driver_module_init_function);
module_exit(driver_module_exit_function);

/* register device. after that the drive is appeared in /proc/devices */
register_chrdrv(major_number, DEVICE_NAME, file_ops);
unregister_chrdrv()

/* create device class */

/* create node under /dev */
```
