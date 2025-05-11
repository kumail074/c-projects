#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void) {
    // pr_info("Hello World\n");
    printk(KERN_INFO "Hello world\n");
    return 0;
}

void cleanup_module(void) {
    pr_info(KERN_INFO "Goodbye Areeqa\n");
}

MODULE_LICENSE("GPL");
