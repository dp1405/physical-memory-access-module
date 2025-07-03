#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const char ____versions[]
__used __section("__versions") =
	"\x10\x00\x00\x00\x09\xcd\x80\xde"
	"ioremap\0"
	"\x1c\x00\x00\x00\x2b\x2f\xec\xe3"
	"alloc_chrdev_region\0"
	"\x18\x00\x00\x00\x0e\x7e\xc4\x33"
	"class_create\0\0\0\0"
	"\x18\x00\x00\x00\x86\xa6\x41\xf6"
	"device_create\0\0\0"
	"\x18\x00\x00\x00\xf9\xbd\x21\x0c"
	"device_destroy\0\0"
	"\x18\x00\x00\x00\xeb\xda\x5c\xfa"
	"class_destroy\0\0\0"
	"\x24\x00\x00\x00\x33\xb3\x91\x60"
	"unregister_chrdev_region\0\0\0\0"
	"\x14\x00\x00\x00\xe0\xa8\x04\xa3"
	"cdev_init\0\0\0"
	"\x14\x00\x00\x00\x50\x1d\xb5\x00"
	"cdev_add\0\0\0\0"
	"\x10\x00\x00\x00\x45\xb4\x19\x0b"
	"ioread8\0"
	"\x18\x00\x00\x00\xe1\xbe\x10\x6b"
	"_copy_to_user\0\0\0"
	"\x14\x00\x00\x00\x07\x2e\x44\xc5"
	"cdev_del\0\0\0\0"
	"\x10\x00\x00\x00\x53\x39\xc0\xed"
	"iounmap\0"
	"\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
	"__fentry__\0\0"
	"\x10\x00\x00\x00\x7e\x3a\x2c\x12"
	"_printk\0"
	"\x1c\x00\x00\x00\xca\x39\x82\x5b"
	"__x86_return_thunk\0\0"
	"\x14\x00\x00\x00\x2e\x37\x8d\x84"
	"iowrite8\0\0\0\0"
	"\x18\x00\x00\x00\xc2\x9c\xc4\x13"
	"_copy_from_user\0"
	"\x1c\x00\x00\x00\xcb\xf6\xfd\xf0"
	"__stack_chk_fail\0\0\0\0"
	"\x18\x00\x00\x00\x76\xf2\x0f\x5e"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "8B25ECB816FD94E043DFBB3");
