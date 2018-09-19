#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define DEVICE_NAME "cpdrng"
#define DRIVER_NAME DEVICE_NAME

#define LOG(level, format, ...) \
  printk(level "[" DRIVER_NAME "] " format, ##__VA_ARGS__)

static int majorNumber;
static int opens = 0;
// static struct class *driver_class = NULL;
// static struct device *driver_device = NULL;

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

static int __init rng_init(void) {
  LOG(KERN_INFO, "initialising");

  majorNumber = register_chrdev(0, DEVICE_NAME, &fops);

  if (majorNumber < 0) {
    LOG(KERN_ALERT, "failed to register character device.\n");
    return majorNumber;
  }

  LOG(KERN_INFO, "registered character device.\n");

  return 0;
}

static void __exit rng_exit(void) {
  LOG(KERN_INFO, "exiting.\n");
  unregister_chrdev(majorNumber, DEVICE_NAME);
}

static int device_open(struct inode *node, struct file *handle)
{
  opens++;

  LOG(KERN_INFO, "device opened %d times\n", opens);

  return 0;
}

static int device_release(struct inode *node, struct file *handle)
{
  opens--;

  LOG(KERN_INFO, "device closed. %d handles remaining.\n", opens);

  return 0;
}

static ssize_t device_read(struct file *handle, char *data, size_t size, loff_t *offset)
{
  LOG(KERN_INFO, "tried reading from the device.\n");
  return -EINVAL;
}

static ssize_t device_write(struct file *handle, const char *data, size_t size, loff_t *offset)
{
  LOG(KERN_INFO, "Tried writing to the device.\n");
  return -EINVAL;
}

module_init(rng_init);
module_exit(rng_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chris Doherty");
MODULE_DESCRIPTION("Random number generator");
MODULE_VERSION("0.1");
