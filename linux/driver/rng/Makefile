obj-m += cpdrng.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd -P) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd -P) clean
install:
	insmod cpdrng.ko
uninstall:
	rmmod cpdrng.ko
