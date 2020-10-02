extern kernel_main, _init, _fini, kernel_virtual_position
; vim: ft=nasm

; Declare multiboot header
MBALIGN 	equ 1 << 0
MEMINFO 	equ 1 << 1
FLAGS			equ MBALIGN | MEMINFO
MAGIC			equ 0x1BADB002
CHECKSUM	equ -(MAGIC + FLAGS)

KERN_VIRT equ 0xC0000000;
KERN_PAGE equ (KERN_VIRT >> 22)

section .data
align 0x1000
BootPageDir:
	dd 0x00000083 
	times (KERN_PAGE - 1) dd 0

	dd 0x00000083 
	times (1024 - KERN_PAGE - 1) dd 0

section .multiboot
MultiBootHeader:
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM


; Initialize a stack
; main code section
section .text

_freeze:
	mov eax, 0xFFFFFFF
_freeze_loop:
	sub eax, 1
	cmp eax, 0
	jne _freeze_loop
	inc byte [0xC00B8000]
	ret
loader equ (_loader - 0xC0000000)
global loader
_loader:
	mov byte [0x000B8000], 'A'
	;setup pageing
	mov ecx, (BootPageDir - KERN_VIRT)
	mov cr3, ecx
	mov	ecx, cr4
	or ecx, 0x00000010
	mov cr4, ecx

	mov ecx, cr0
	or ecx, 0x80000001
	mov cr0, ecx

	lea ecx, [_start]
	jmp ecx

_start:
	;mov dword [BootPageDir], 0
	invlpg [0] ;invalidate the first page it is no longer needed

	mov esp, stack_top
	
	call _init
	call kernel_main
	call _fini

	cli
.hang:
	nop
	jmp .hang
section .bss
align 16
stack_bottom:
resb 16384
stack_top:

