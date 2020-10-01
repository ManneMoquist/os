##THIS IS A TERRIBLE MAKEFILE, BUT I JUST WANT THE PROJECT UP AND RUNNING
CC=
CFLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -Iinclude
LFLAGS=-lgcc -L./libs -lk
ARCH=i686
NASM_FLAGS=-felf32

CC:=$(ARCH)-elf-g++
NASM:=nasm
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
KERNEL_OFILES=obj/vga.o obj/entry.o obj/terminal.o obj/asm/boot.o
KERNEL_OBJ:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(KERNEL_OFILES) $(CRTEND_OBJ) $(CRTN_OBJ)

LIBK_CFLAGS=-O2 -g -Wall -Wextra -ffreestanding -D__is_libc -I$(LIBK_INCLUDE) -D__is_libk
LIBK_INCLUDE?=libc/include
LIBK_H:=libc/include/stdio.h libc/include/string.h
LIBK_SRC := $(patsubst libc/include/%.h, libc/%/*.c, $(LIBK_H))
LIBK_SRC := $(wildcard $(LIBK_SRC))
LIBK_OBJ:= $(patsubst libc/%.c, obj/libk/%.o, $(LIBK_SRC))

all: libs/libk.a MOS.bin
	-ctags -R
bin: MOS.bin
libc: libc.a

obj/%.o: kernel/%.cpp $(KERNEL_H)
	$(CC) -c -o $@ $<  $(CFLAGS)

obj/asm/%.o: kernel/asm/%.asm
	-mkdir -p obj/asm
	$(NASM) $(NASM_FLAGS) $< -o $@

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
	@echo $(LIBK_OBJ)
	-rm MOS.bin
	-find ./obj/ -name \*.o -type f -delete
	-find ./libs/ -name \*.a -type f -delete

