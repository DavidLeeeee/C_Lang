	.file	"01_array_pointer.c"
	.text
	.section	.rodata
.LC0:
	.string	"[inspect_array_parameter]"
.LC1:
	.string	"sizeof(arr_param) = %zu\n"
.LC2:
	.string	"count             = %zu\n"
.LC3:
	.string	"arr_param         = %p\n"
.LC4:
	.string	"arr_param + 1     = %p\n"
	.text
	.type	inspect_array_parameter, @function
inspect_array_parameter:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$8, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	addq	$4, %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	inspect_array_parameter, .-inspect_array_parameter
	.section	.rodata
.LC5:
	.string	"[main]"
.LC6:
	.string	"sizeof(arr)       = %zu\n"
.LC7:
	.string	"sizeof(ptr)       = %zu\n"
.LC8:
	.string	"&arr[0]           = %p\n"
.LC9:
	.string	"arr               = %p\n"
.LC10:
	.string	"ptr               = %p\n"
.LC11:
	.string	"arr + 1           = %p\n"
.LC12:
	.string	"ptr + 1           = %p\n"
.LC13:
	.string	"*(arr + 2)        = %d\n"
.LC14:
	.string	"ptr[2]            = %d\n"
.LC15:
	.string	"\nQuestions:"
	.align 8
.LC16:
	.string	"1. \354\231\234 sizeof(arr)\354\231\200 sizeof(arr_param)\352\260\200 \353\213\244\353\245\270\352\260\200?"
	.align 8
.LC17:
	.string	"2. arr\354\231\200 ptr\354\235\230 \354\266\234\353\240\245 \354\243\274\354\206\214\353\212\224 \353\271\204\354\212\267\355\225\234\353\215\260 \354\231\234 \352\260\231\354\235\200 \352\260\234\353\205\220\354\235\264 \354\225\204\353\213\214\352\260\200?"
	.align 8
.LC18:
	.string	"3. \355\225\250\354\210\230 \354\235\270\354\236\220\353\241\234 \353\204\230\352\270\260\353\212\224 \354\210\234\352\260\204 \353\260\260\354\227\264\354\235\200 \353\254\264\354\227\207\354\234\274\353\241\234 \353\260\224\353\200\214\353\212\224\352\260\200?"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$10, -32(%rbp)
	movl	$20, -28(%rbp)
	movl	$30, -24(%rbp)
	movl	$40, -20(%rbp)
	movl	$50, -16(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, -40(%rbp)
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$20, %esi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$8, %esi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-40(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-32(%rbp), %rax
	addq	$4, %rax
	movq	%rax, %rsi
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-40(%rbp), %rax
	addq	$4, %rax
	movq	%rax, %rsi
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-32(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	inspect_array_parameter
	leaq	.LC15(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC16(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC17(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC18(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L4
	call	__stack_chk_fail@PLT
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
