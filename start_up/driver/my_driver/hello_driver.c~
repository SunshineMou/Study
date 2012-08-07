/*!
 * \file	hello_driver.c
 * \brief	
 * \author	SunshineMou
 * contact  qingtianmou@gmail.com
 * \version	0.00
 * \date	12-03-29 23:00:33
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
    printk(KERN_ALERT "Hello, world\n");
    return 0;
}
static void hello_exit(void)
{

    printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
