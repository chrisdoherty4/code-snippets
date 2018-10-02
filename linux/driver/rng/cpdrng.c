#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/random.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "cpdrng"
#define DRIVER_NAME DEVICE_NAME

#define LOG(level, format, ...) \
  printk(level "[" DRIVER_NAME "] " format, ##__VA_ARGS__)

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
  .open = device_open,
  .release = device_release,
  .read = device_read,
  .write = device_write
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

  cdev_init(&cdev_struct, &fops);
  device_class = class_create(THIS_MODULE, DEVICE_NAME "_class");
  device_struct = device_create(
    device_class,
    NULL,
    device_number,
    NULL,
    DEVICE_NAME
  );
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
  int ret = 0;
  char bytes[size];
  memset(bytes, 0, size);

  LOG(KERN_INFO, "created buffer of size %ld\n", size);

  LOG(KERN_INFO, "generating random bytes.\n");
  get_random_bytes(bytes, size);

  LOG(KERN_INFO, "copying data to user space\n");
  ret = copy_to_user(data, bytes, size);

  if (ret != 0) {
    LOG(KERN_INFO, "failed to copy bytes to user space %d\n", ret);
    return ret;
  }

  LOG(KERN_INFO, "read complete\n");

  return size;
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
