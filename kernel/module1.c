#include "/home/haider/linux-6.13.1/include/linux/printk.h"
#include <linux/module.h>   

int init_module(void) {
    pr_info("Hello Patch. This is my first kernel module.\n");
    return 0;
}

void cleanup_module(void) {
    pr_info("See you later, Areeqa\n");
}
