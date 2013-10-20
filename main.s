	.file	"main.cpp"
	.text
	.p2align 4,,15
	.type	_ZL4workii, @function
_ZL4workii:
.LFB1:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	%edi, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movl	%esi, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movl	$2000000000, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L3:
	leal	(%r12,%rbx), %esi
	leal	0(%r13,%rbx), %edi
	call	_ZL3addRKiS0_.isra.0
	addl	%eax, %ebx
	subl	$1, %ebp
	jne	.L3
	movl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1:
	.size	_ZL4workii, .-_ZL4workii
	.p2align 4,,15
	.type	_ZL3addRKiS0_.isra.0, @function
_ZL3addRKiS0_.isra.0:
.LFB3:
	.cfi_startproc
	leal	(%rdi,%rsi), %eax
	ret
	.cfi_endproc
.LFE3:
	.size	_ZL3addRKiS0_.isra.0, .-_ZL3addRKiS0_.isra.0	
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	movq	%rsi, %rax
	movq	16(%rsi), %rdx
	movq	8(%rax), %rax
	movsbl	(%rdx), %esi
	movsbl	(%rax), %edi
	jmp	_ZL4workii
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.2-2ubuntu1) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
