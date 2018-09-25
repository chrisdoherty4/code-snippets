#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/random.h>
#include <asm/uaccess.h>
#include <asm/error.h>

#define DEVICE_NAME "cpdrng"
#define DRIVER_NAME DEVICE_NAME

#define LOG(level, format, ...) \
  printk(level "[" DRIVER_NAME "] " format, ##__VA_ARGS__)

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
  open: device_open,
  release: device_release,
  read: device_read,
  write: device_write
};

static struct class *device_class = NULL;
static dev_t device_number;
static struct cdev cdev_struct;
static struct device *device_struct;

static int __init rng_init(void) {
  int retval = 0;

  LOG(KERN_INFO, "initialising");

  retval = alloc_chrdev_region(&device_number, 0, 1, DEVICE_NAME);

  if (retval != 0) {
    printk(KERN_ERR "Could not allocate character device region");
  }

  device_class = class_create(THIS_MODULE, DEVICE_NAME "_class");

  cdev_init(&cdev_struct, &fops);

  device_struct = device_create(device_class, NULL, device_number, NULL, DEVICE_NAME);

  cdev_add(&cdev_struct, device_number, 1);

  return 0;
}

static void __exit rng_exit(void) {
  LOG(KERN_INFO, "exiting.\n");

  cdev_del(&cdev_struct);

  device_destroy(device_class, device_number);

  class_destroy(device_class);

  unregister_chrdev_region(device_number, 1);
}

static int device_open(struct inode *node, struct file *handle)
{
  return 0;
}

static int device_release(struct inode *node, struct file *handle)
{
  return 0;
}

static ssize_t device_read(struct file *handle, char *data, size_t size, loff_t *offset)
{
  LOG(KERN_INFO, "tried reading from the device.\n");

  char bytes[256] = {0};

  get_random_bytes(bytes, sizeof(bytes));



  return 0;
}

static ssize_t device_write(struct file *handle, const char *data, size_t size, loff_t *offset)
{
  LOG(KERN_INFO, "tried writing to the device.\n");
  return -EINVAL;
}

module_init(rng_init);
module_exit(rng_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chris Doherty");
MODULE_DESCRIPTION("Random number generator");
MODULE_VERSION("0.1");
