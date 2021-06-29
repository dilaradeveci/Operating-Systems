obj-m += p3_a1.o
obj-m += p3_a2.o
obj-m += p3_b.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
