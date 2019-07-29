##THIS IS A TERRIBLE MAKEFILE, BUT I JUST WANT THE PROJECT UP AND RUNNING
CC=
CFLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib
LFLAGS=-lgcc
ASMC=
ARCH=i686

KERNELLINKFILE=kernel/link/link.ld

KERNELOBJECTS:=obj/entry.o obj/vga.o
KERNELSOURCE:=kernel/entry.cpp kernel/vga.cpp
KERNELHEADER:=kernel/vga.h


CC:=$(ARCH)-elf-g++
ASMC:=$(ARCH)-elf-as
ASMFILES:=$(foreach dir, $(ASMDIRS), $(ASMFILEWILD))
ASM_OUT:=$(addprefix obj/, $(addsuffix .o, $(notdir $(ASMFILES))))

KERNELCFILES:=$(foreach dir, $(KERNELCDIR), $(CPPFILEWILD))
KERNELDEPS:=$(foreach dir, $(KERNELCDIR), $(HFILEWILD))
KERNEL_OUT:=$(addprefix obj/, $(addsuffix .o, $(notdir $(KERNELCFILES))))
LINKLIST=obj/vga.o obj/entry.o obj/asm/boot.o

CRTI_OBJ=obj/asm/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=obj/asm/crtn.o

OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(LINKLIST) $(CRTEND_OBJ) $(CRTN_OBJ)
INTERNAL_OBJS:=$(CRTI_OBJ) $(LINKLIST) $(CRTN_OBJ)


obj/%.o: kernel/%.cpp $(KERNELHEADER)
	$(CC) -c -o $@ $<  $(CFLAGS)

obj/asm/%.o: kernel/asm/%.s 
	$(ASMC) $< -o $@

kernellink: $(OBJ_LINK_LIST)
	$(CC) -T $(KERNELLINKFILE) $(OBJ_LINK_LIST) $(CFLAGS) $(LFLAGS) -o MOS.bin 

	
clean:
	-rm MOS.bin
	-find ./obj/ -name \*.o -type f -delete

