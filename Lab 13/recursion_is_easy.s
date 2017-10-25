	.file	"recursion_is_easy.c"
	.section	.rodata
.LC0:
	.string	"fact(%d) == %d == 0x%x"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$1, %edi
	call	factorial
	movl	%eax, %ebx
	movl	$1, %edi
	call	factorial
	movl	%ebx, %ecx
	movl	%eax, %edx
	movl	$1, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$2, %edi
	call	factorial
	movl	%eax, %ebx
	movl	$2, %edi
	call	factorial
	movl	%ebx, %ecx
	movl	%eax, %edx
	movl	$2, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$5, %edi
	call	factorial
	movl	%eax, %ebx
	movl	$5, %edi
	call	factorial
	movl	%ebx, %ecx
	movl	%eax, %edx
	movl	$5, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$7, %edi
	call	factorial
	movl	%eax, %ebx
	movl	$7, %edi
	call	factorial
	movl	%ebx, %ecx
	movl	%eax, %edx
	movl	$7, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	factorial
	.type	factorial, @function
factorial:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	%edi, -20(%rbp)
	cmpl	$1, -20(%rbp)
	je	.L4
	cmpl	$0, -20(%rbp)
	jne	.L5
.L4:
	movl	-20(%rbp), %eax
	jmp	.L6
.L5:
	movl	-20(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	call	factorial
	movl	%eax, %ebx
	movl	-20(%rbp), %eax
	subl	$2, %eax
	movl	%eax, %edi
	call	factorial
	addl	%ebx, %eax
.L6:
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	factorial, .-factorial
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
