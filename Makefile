##THIS IS A TERRIBLE MAKEFILE, BUT I JUST WANT THE PROJECT UP AND RUNNING
CC=
CFLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib
LFLAGS=-lgcc
ASMC=
ARCH=i686

OBJDIR=obj
OBJFILEWILD=$(wildcard $(dir)/*.o)
LINKLIST=

ASMDIRS=kernel/boot
ASMFILEWILD=$(wildcard $(dir)/*.s)

KERNELCDIR=kernel
CPPFILEWILD=$(wildcard $(dir)/*.c*)
HFILEWILD=$(wildcard $(dir)/*.h)

KERNELLINKFILE=kernel/link/link.ld


CC:=$(ARCH)-elf-g++
ASMC:=$(ARCH)-elf-as
ASMFILES:=$(foreach dir, $(ASMDIRS), $(ASMFILEWILD))
KERNELCFILES:=$(foreach dir, $(KERNELCDIR), $(CPPFILEWILD))
LINKLIST:=$(foreach dir, $(OBJDIR), $(OBJFILEWILD))

all:
	echo $(KERNELCFILES)
	$(MAKE) build
	$(MAKE) link

build:
	echo $(ASMFILES)
	for file in $(ASMFILES); do \
		outname=$$(basename $$file).o; \
		$(ASMC) $$file -o $(OBJDIR)/$$outname ; \
	done

#	$(CC) -c $(KERNELCFILES) -o $(OBJDIR)/test.o $(CFLAGS)
	for file in $(KERNELCFILES); do \
		outname=$$(basename $$file).o; \
		$(CC) -c $$file -o $(OBJDIR)/$$outname $(CFLAGS); \
	done

link:
	$(CC) -T $(KERNELLINKFILE) -o MOS.bin $(CFLAGS) $(LINKLIST) $(LFLAGS)
	
clean:
	-rm MOS.bin
	-rm obj/*.o

