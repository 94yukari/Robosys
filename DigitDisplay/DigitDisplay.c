
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<asm/uaccess.h>
#include<linux/io.h>

MODULE_AUTHOR("YUKARI SUZUKI,RYUICHI UEDA");
MODULE_DESCRIPTION("driver for 7 LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");


static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base_A = NULL;
static volatile u32 *gpio_base_B = NULL;
static volatile u32 *gpio_base_C = NULL;
static volatile u32 *gpio_base_D = NULL;
static volatile u32 *gpio_base_E = NULL;
static volatile u32 *gpio_base_F = NULL;
static volatile u32 *gpio_base_G = NULL;

static ssize_t led_write(struct file* filp,const char* buf,size_t count,loff_t*pos){
	char c;
	if(copy_from_user(&c,buf,sizeof(char)))
	return -EFAULT;

	if(c == '0'){
		gpio_base_A[10] = 1 << 20;
		gpio_base_B[10] = 1 << 21;
		gpio_base_C[10] = 1 << 22;
		gpio_base_D[10] = 1 << 23;
		gpio_base_E[10] = 1 << 24;
		gpio_base_F[10] = 1 << 25;
		gpio_base_G[7] = 1 << 26;
	}else if(c == '1'){
		gpio_base_A[7] = 1 << 20;
		gpio_base_B[10] = 1 << 21;
		gpio_base_C[10] = 1 << 22;
		gpio_base_D[7] = 1 << 23;
		gpio_base_E[7] = 1 << 24;
		gpio_base_F[7] = 1 << 25;
		gpio_base_G[7] = 1 << 26;
	}else if(c == '2'){
		gpio_base_A[10] = 1 << 20;
		gpio_base_B[10] = 1 << 21;
		gpio_base_C[7] = 1 << 22;
		gpio_base_D[10] = 1 << 23;
		gpio_base_E[10] = 1 << 24;
		gpio_base_F[7] = 1 << 25;
		gpio_base_G[10] = 1 << 26;
	}else if(c == '3'){
		gpio_base_A[10] = 1 << 20;
		gpio_base_B[10] = 1 << 21;
		gpio_base_C[10] = 1 << 22;
		gpio_base_D[10] = 1 << 23;
		gpio_base_E[7] = 1 << 24;
		gpio_base_F[7] = 1 << 25;
		gpio_base_G[10] = 1 << 26;
	}else if(c == '4'){
		gpio_base_A[7] = 1 << 20;
		gpio_base_B[10] = 1 << 21;
		gpio_base_C[10] = 1 << 22;
		gpio_base_D[7] = 1 << 23;
		gpio_base_E[7] = 1 << 24;
		gpio_base_F[10] = 1 << 25;
		gpio_base_G[10] = 1 << 26;
	}else if(c == '5'){
		gpio_base_A[10] = 1 << 20;
		gpio_base_B[7] = 1 << 21;
		gpio_base_C[10] = 1 << 22;
		gpio_base_D[10] = 1 << 23;
		gpio_base_E[7] = 1 << 24;
		gpio_base_F[10] = 1 << 25;
		gpio_base_G[10] = 1 << 26;
	}else if(c == '6'){
		gpio_base_A[10] = 1 << 20;
		gpio_base_B[7] = 1 << 21;
		gpio_base_C[10] = 1 << 22;
		gpio_base_D[10] = 1 << 23;
		gpio_base_E[10] = 1 << 24;
		gpio_base_F[10] = 1 << 25;
		gpio_base_G[10] = 1 << 26;
	}else if(c == '7'){
		gpio_base_A[10] = 1 << 20;
		gpio_base_B[10] = 1 << 21;
		gpio_base_C[10] = 1 << 22;
		gpio_base_D[7] = 1 << 23;
		gpio_base_E[7] = 1 << 24;
		gpio_base_F[10] = 1 << 25;
		gpio_base_G[7] = 1 << 26;
	}else if(c == '8'){
		gpio_base_A[10] = 1 << 20;
		gpio_base_B[10] = 1 << 21;
		gpio_base_C[10] = 1 << 22;
		gpio_base_D[10] = 1 << 23;
		gpio_base_E[10] = 1 << 24;
		gpio_base_F[10] = 1 << 25;
		gpio_base_G[10] = 1 << 26;
	}else if(c == '9'){
		gpio_base_A[10] = 1 << 20;
		gpio_base_B[10] = 1 << 21;
		gpio_base_C[10] = 1 << 22;
		gpio_base_D[10] = 1 << 23;
		gpio_base_E[7] = 1 << 24;
		gpio_base_F[10] = 1 << 25;
		gpio_base_G[10] = 1 << 26;
	}
	printk(KERN_INFO"receive %c\n",c);
	return 1;

}

static ssize_t sushi_read(struct file* filp, char* buf, size_t count,loff_t* pos){
	int size = 0;
	char sushi[] = {0xF0,0x9F,0x8D,0xA3,0x0A};
	if(copy_to_user(buf+size,(const char *)sushi,sizeof(sushi))){
	printk(KERN_INFO"sushi : copy_to_user failed\n");
	return -EFAULT;
	}
	size += sizeof(sushi);
	return size;

}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write,
	.read = sushi_read
};

static int __init init_mod(void)
{
	int retval;
		
	gpio_base_A = ioremap_nocache(0x3f200000, 0xA0);	
	gpio_base_B = ioremap_nocache(0x3f200000, 0xA0);
	gpio_base_C = ioremap_nocache(0x3f200000, 0xA0);	
	gpio_base_D = ioremap_nocache(0x3f200000, 0xA0);
	gpio_base_E = ioremap_nocache(0x3f200000, 0xA0);	
	gpio_base_F = ioremap_nocache(0x3f200000, 0xA0);
	gpio_base_G = ioremap_nocache(0x3f200000, 0xA0);	

	
	
	const u32 led_A = 20;
	const u32 index_A = led_A/10;
	const u32 shift_A = (led_A%10)*3;
	const u32 mask_A = ~(0x7 << shift_A);
	gpio_base_A[index_A] = (gpio_base_A[index_A] & mask_A) | (0x1 << shift_A);
	
	const u32 led_B = 21;
	const u32 index_B = led_B/10;
	const u32 shift_B = (led_B%10)*3;
	const u32 mask_B = ~(0x7 << shift_B);
	gpio_base_B[index_B] = (gpio_base_B[index_B] & mask_B) | (0x1 << shift_B);
	
	const u32 led_C = 22;
	const u32 index_C = led_C/10;
	const u32 shift_C = (led_C%10)*3;
	const u32 mask_C = ~(0x7 << shift_C);
	gpio_base_C[index_C] = (gpio_base_C[index_C] & mask_C) | (0x1 << shift_C);
	
	const u32 led_D = 23;
	const u32 index_D = led_D/10;
	const u32 shift_D = (led_D%10)*3;
	const u32 mask_D = ~(0x7 << shift_D);
	gpio_base_D[index_D] = (gpio_base_D[index_D] & mask_D) | (0x1 << shift_D);
	
	const u32 led_E = 24;
	const u32 index_E = led_E/10;
	const u32 shift_E = (led_E%10)*3;
	const u32 mask_E = ~(0x7 << shift_E);
	gpio_base_E[index_E] = (gpio_base_E[index_E] & mask_E) | (0x1 << shift_E);
	const u32 led_F = 25;
	const u32 index_F = led_F/10;
	const u32 shift_F = (led_F%10)*3;
	const u32 mask_F = ~(0x7 << shift_F);
	gpio_base_F[index_F] = (gpio_base_F[index_F] & mask_F) | (0x1 << shift_F);

	const u32 led_G = 26;
	const u32 index_G = led_G/10;
	const u32 shift_G = (led_G%10)*3;
	const u32 mask_G = ~(0x7 << shift_G);
	gpio_base_G[index_G] = (gpio_base_G[index_G] & mask_G) | (0x1 << shift_G);
	
	retval = alloc_chrdev_region(&dev,0,1,"myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}
	
	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));
	
	cdev_init(&cdv,&led_fops);
	retval = cdev_add(&cdv,dev,1);
	if(retval<0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d\n",MAJOR(dev),MINOR(dev));
	}

	cls = class_create(THIS_MODULE,"myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}
	device_create(cls,NULL,dev,NULL,"myled%d",MINOR(dev));

	return 0;
}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls,dev);
	class_destroy(cls);
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);

