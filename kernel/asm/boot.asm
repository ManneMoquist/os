; Declare multiboot header
MBALIGN 	equ 1 << 0
MEMINFO 	equ 1 << 1
FLAGS			equ MBALIGN | MEMINFO
MAGIC			equ 0x1BADB002
CHECKSUM	equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

; Initialize a stack
section .bss
align 16
stack_bottom:
resb 16384
stack_top:

; main code section
section .text
global _start:function (_start.end - _start)
_start:
	mov esp, stack_top
	extern _init
	extern _fini
	extern kernel_main

	call _init
	call kernel_main
	call _fini

	cli
.hang hlt
	jmp .hang
.end:
