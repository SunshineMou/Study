A=ar
ARCH=
CC=gcc
LDFLAGS =
obj-m :=hello_driver.o
KERNELDIR :=/usr/src/linux-headers-3.0.0-16-generic 
PWD    :=$(shell pwd)
modules:
	    $(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	    rm *.ko *.mod* *.symvers  *.order
