#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/device.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<asm/io.h>

#define VRAM_BASE 0x000A0000
#define VRAM_SIZE 0x00020000

static dev_t first;
static int num_of_device_files=3;
static struct class *cl;
static struct cdev c_dev;
static void __iomem *vram;

static int my_open(struct inode *i, struct file *f){
    printk(KERN_INFO "pmad: open() was called!\n");
    return 0;
}

static int my_close(struct inode *i, struct file *f){
    printk(KERN_INFO "pmad: close() was called!\n");
    return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *offset){
    u8 byte;

    if(*offset>=VRAM_SIZE){
        return 0;
    }

    if(*offset+len>VRAM_SIZE){
        len = VRAM_SIZE - *offset;
    }

    for(int i=0;i<len;i++){
        byte = ioread8((u8*)vram + *offset + i);

        if(copy_to_user(buf+i, &byte, 1)){
            return -EFAULT;
        }
    }

    *offset+=len;

    return len;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *offset){
    u8 byte;
    
    if(*offset >= VRAM_SIZE){
        return 0;
    }

    if(*offset+len > VRAM_SIZE){
        len=VRAM_SIZE-*offset;
    }

    for(int i=0;i<len;i++){
        if(copy_from_user(&byte, buf+i, 1)){
            return -EFAULT;
        }

        iowrite8(byte, (u8 *)vram + *offset + i);
    }

    *offset+=len;

    return len;
}

static struct file_operations my_ops= {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write
};

static int __init pmad_init(void){

    int ret;
    struct device *dev_ret;

    if((vram = ioremap(VRAM_BASE, VRAM_SIZE))==NULL){
        printk(KERN_ERR "pmad: Error mapping physical memory at physical address 0x%d to virtual memory\n", VRAM_BASE);

        return -ENOMEM;
    }

    if((ret = alloc_chrdev_region(&first, 0, num_of_device_files, "pmad")) < 0){  //int alloc_chrdev_region(dev_t *first, unsigned int firstminor, unsigned int cnt, char *name);
        printk(KERN_ERR "pmad: failed allocating region for character devices\n");
        return ret;
    }

    if(IS_ERR(cl = class_create("pmad"))){
        printk(KERN_ERR "pmad: error creating class in /sys/class/ directory\n");
        unregister_chrdev_region(first, num_of_device_files);

        return PTR_ERR(cl);
    }

    for(int i=0;i<num_of_device_files;i++){
        if(IS_ERR(dev_ret = device_create(cl,NULL,MKDEV(MAJOR(first),MINOR(first)+i),NULL,"pmad%d",i))){
            printk(KERN_ERR "pmad: error creating device files in /dev/ directory\n");

            for(int j=0;j<i;j++){
                device_destroy(cl,MKDEV(MAJOR(first),MINOR(first)+j));
            }

            class_destroy(cl);
            unregister_chrdev_region(first, num_of_device_files);

            return PTR_ERR(dev_ret);
        }
    }

    printk(KERN_INFO "pmad: <Major, Minor>: <%d, %d>\n", MAJOR(first), MINOR(first));

    cdev_init(&c_dev, &my_ops);
    if((ret = cdev_add(&c_dev, first, num_of_device_files)) < 0){
        for(int i=0;i<num_of_device_files;i++){
            device_destroy(cl,MKDEV(MAJOR(first),MINOR(first)+i));
        }
        class_destroy(cl);
        unregister_chrdev_region(first, num_of_device_files);

        printk(KERN_ERR "pmad: Error inserting operations on device files!\n");

        return ret;
    }

    printk(KERN_INFO "pmad: Initialized\n");

    return 0;
}

static void __exit pmad_exit(void){
    cdev_del(&c_dev);

    for(int i=0;i<num_of_device_files;i++){
        device_destroy(cl,MKDEV(MAJOR(first),MINOR(first)+i));
    }
    class_destroy(cl);
    unregister_chrdev_region(first, num_of_device_files);

    iounmap(vram);

    printk(KERN_INFO "pmad: exited\n");
}

module_init(pmad_init);
module_exit(pmad_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("drpn14  <darpan1405@gmail.com>");
MODULE_DESCRIPTION("Character Device Module to Access Physical Memory");
