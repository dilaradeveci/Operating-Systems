#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
}birthday;

static LIST_HEAD(birthday_list);


/* Module entry point */
int birthdayList_init(void) {
	printk(KERN_INFO "Creating birthday list\n");
	
	//person1
	struct birthday *dilara;
	dilara = kmalloc(sizeof(*dilara), GFP_KERNEL);
	dilara->day = 30;
	dilara->month = 8;
	dilara->year = 2000;
	INIT_LIST_HEAD(&dilara->list);
	list_add_tail(&dilara->list, &birthday_list);

	//person2
	struct birthday *ayse;
	ayse = kmalloc(sizeof(*ayse), GFP_KERNEL);
	ayse->day = 17;
	ayse->month = 4;
	ayse->year = 1970;
	INIT_LIST_HEAD(&ayse->list);
	list_add_tail(&ayse->list, &birthday_list);

	//person3
	struct birthday *mus;
	mus = kmalloc(sizeof(*mus), GFP_KERNEL);
	mus->day = 29;
	mus->month = 3;
	mus->year = 1968;
	INIT_LIST_HEAD(&mus->list);
	list_add_tail(&mus->list, &birthday_list);

	//person4
	struct birthday *memo;
	memo = kmalloc(sizeof(*memo), GFP_KERNEL);
	memo->day = 10;
	memo->month = 6;
	memo->year = 2004;
	INIT_LIST_HEAD(&memo->list);
	list_add_tail(&memo->list, &birthday_list);

	//person5
	struct birthday *mert;
	mert = kmalloc(sizeof(*mert), GFP_KERNEL);
	mert->day = 4;
	mert->month = 1;
	mert->year = 2000;
	INIT_LIST_HEAD(&mert->list);
	list_add_tail(&mert->list, &birthday_list);

	printk(KERN_INFO "Traversing birthday list\n");
	struct birthday *ptr;
	list_for_each_entry(ptr, &birthday_list, list) {
		printk(KERN_INFO "BIRTHDAY: Month: %d Day: %d Year: %d\n", ptr->month, ptr->day, ptr->year);
	}
	printk(KERN_INFO "Done\n");
	return 0;
}

/* Module exit point */
void birthdayList_exit(void) {
	printk(KERN_INFO "Removing module\n");

/* Removes each struct from list */
	struct birthday *ptr, *nxt;
	list_for_each_entry_safe(ptr, nxt, &birthday_list, list) {
		printk(KERN_INFO "REMOVING BIRTHDAY: Month: %d Day: %d Year: %d\n", ptr->month, ptr->day, ptr->year);
		list_del(&ptr->list);
		kfree(ptr);
	}
}

/* Register module entry/exit pts */

module_init(birthdayList_init);
module_exit(birthdayList_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Birthday List of Dilara");
MODULE_AUTHOR("Dİlara Deveci");
