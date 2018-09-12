obj-m += rng.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd -P) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd -P) clean
