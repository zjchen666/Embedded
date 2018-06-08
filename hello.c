/* hello.c
 *
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zhijun Chen");
MODULE_DESCRIPTION("simplest char device driver");
MODULE_VERSION("0.1");

/* Prototypes */
int __init add_module(void);
void __exit remove_module(void);
static int device_open( struct inode* inode, struct file* file);
static int device_release( struct inode* inode, struct file* file);
static int device_ioctl( struct file* file, unsigned int cmd, unsigned long arg);

/* File operation structure */
static struct file_operations ops = {
	.open = device_open,
	.release = device_release
/*	.unlocked_ioctl = device_ioctl*/
};

/* static variables*/
static int major = 0;
#define DEVICE_NAME  "hello"

int __init add_module(void)
{
	printk(KERN_INFO "Hello World!\n");
	major = register_chrdev(0, DEVICE_NAME, &ops);
	printk("The major number is: %d\n", major);
	return 0;
}

void __exit remove_module(void)
{
	printk(KERN_INFO "release module!\n");
	unregister_chrdev(major, DEVICE_NAME);
	return;
}

static int device_open( struct inode* inode, struct file* file)
{
	return 0;
}

static int device_release( struct inode* inode, struct file* file)
{
	return 0;
}

static int device_ioctl( struct file* file, unsigned int cmd, unsigned long arg)
{
   return 0;
}

module_init(add_module)
module_exit(remove_module)
