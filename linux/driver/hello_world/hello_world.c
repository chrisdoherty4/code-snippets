#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chris Doherty");
MODULE_DESCRIPTION("Example Hello World kernel module.");
MODULE_VERSION("0.01");

static int __init hello_world_init(void) {
  printk(KERN_INFO "hello_world: initialising\n");
  return 0;
}

static void __exit hello_world_exit(void) {
  printk(KERN_INFO "hello_world: exiting\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);
