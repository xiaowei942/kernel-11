obj-y += pmm.o

all:
	make -C /armboot/nfsroot-00/linux_src/linux-2.6.24 M=$(PWD) modules
	arm-linux-gcc -o pmm_test -I /armboot/nfsroot-00/linux_src/linux-2.6.24/include pmm_test.c
       
clean:
	make -C /armboot/nfsroot-00/linux_src/linux-2.6.24 M=$(PWD) clean
	rm -rf *.o
	rm -rf pmm_test
install:
	cp pmm.ko pmm_test /armboot/nfsroot-00/pmm
