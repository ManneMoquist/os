##THIS IS A TERRIBLE MAKEFILE, BUT I JUST WANT THE PROJECT UP AND RUNNING
CC=
CFLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -Iinclude
LFLAGS=-lgcc -L./libs -lk
ASMC=
ARCH=i686


CC:=$(ARCH)-elf-g++
ASMC:=$(ARCH)-elf-as
AR:=$(ARCH)-elf-ar

ASMFILES:=$(foreach dir, $(ASMDIRS), $(ASMFILEWILD))
ASM_OUT:=$(addprefix obj/, $(addsuffix .o, $(notdir $(ASMFILES))))

CRTI_OBJ=obj/asm/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=obj/asm/crtn.o

KERNELLINKFILE=kernel/link/link.ld

KERNEL_SRC:=kernel/entry.cpp kernel/vga.cpp kernel/terminal.cpp
KERNEL_H:=kernel/vga.h kernel/terminal.h
KERNEL_OFILES=obj/vga.o obj/entry.o obj/asm/boot.o obj/terminal.o
KERNEL_OBJ:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(KERNEL_OFILES) $(CRTEND_OBJ) $(CRTN_OBJ)

LIBK_CFLAGS=-O2 -g -Wall -Wextra -ffreestanding -D__is_libc -I$(LIBK_INCLUDE) -D__is_libk
LIBK_INCLUDE?=libc/include
LIBK_SRC:=\
	libc/stdio/printf.c\
	libc/stdio/putchar.c\
	libc/string/memchr.c\
	libc/string/memcmp.c\
	libc/string/memcpy.c\
	libc/string/memmove.c\
	libc/string/memset.c\
	libc/string/strcat.c\
	libc/string/strncat.c\
	libc/string/strchr.c\
	libc/string/strcmp.c\
	libc/string/strncmp.c\
	libc/string/strcoll.c\
	libc/string/strcpy.c\
	libc/string/strncpy.c\
	libc/string/strcspn.c\
	libc/string/strlen.c\
	libc/string/strpbrk.c\
	libc/string/strrchr.c\
	libc/string/strspn.c\
	libc/string/strstr.c\
	libc/string/strtok.c
LIBK_H:=libc/include/stdio.h libc/include/string.h
LIBK_OBJ:=\
	obj/libk/stdio/printf.o\
	obj/libk/stdio/putchar.o\
	obj/libk/string/memchr.o\
	obj/libk/string/memcmp.o\
	obj/libk/string/memcpy.o\
	obj/libk/string/memmove.o\
	obj/libk/string/memset.o\
	obj/libk/string/strcat.o\
	obj/libk/string/strncat.o\
	obj/libk/string/strchr.o\
	obj/libk/string/strcmp.o\
	obj/libk/string/strncmp.o\
	obj/libk/string/strcoll.o\
	obj/libk/string/strcpy.o\
	obj/libk/string/strncpy.o\
	obj/libk/string/strcspn.o\
	obj/libk/string/strlen.o\
	obj/libk/string/strpbrk.o\
	obj/libk/string/strrchr.o\
	obj/libk/string/strspn.o\
	obj/libk/string/strstr.o\
	obj/libk/string/strtok.o

all: libs/libk.a MOS.bin
	-ctags -R
bin: MOS.bin
libc: libc.a

obj/%.o: kernel/%.cpp $(KERNEL_H)
	$(CC) -c -o $@ $<  $(CFLAGS)

obj/asm/%.o: kernel/asm/%.s 
	-mkdir -p obj/asm
	$(ASMC) $< -o $@

obj/libk/stdio/%.o: libc/stdio/%.c $(LIBK_H)
	-mkdir -p obj/libk/stdio
	$(CC) -c $< -o $@  $(LIBK_CFLAGS)

obj/libk/string/%.o: libc/string/%.c $(LIBK_H)
	-mkdir -p obj/libk/string
	$(CC) -c $< -o $@  $(LIBK_CFLAGS)

libs/libk.a: $(LIBK_OBJ)
	-mkdir -p libs
	-mkdir -p libc/include
	-mkdir -p include
	-cp libc/include/* include/
	$(AR) rcs $@ $(LIBK_OBJ)

MOS.bin: $(KERNEL_OBJ) libs/libk.a
	$(CC) -T $(KERNELLINKFILE) $(KERNEL_OBJ) $(CFLAGS) $(LFLAGS) -o MOS.bin



	
clean:
	-rm MOS.bin
	-find ./obj/ -name \*.o -type f -delete
	-find ./libs/ -name \*.a -type f -delete

