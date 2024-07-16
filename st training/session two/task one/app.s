	.file	"app.c"
	.text
	.globl	expected_salary
	.data
	.align 4
	.type	expected_salary, @object
	.size	expected_salary, 4
expected_salary:
	.long	5000
	.globl	real_salary
	.bss
	.align 4
	.type	real_salary, @object
	.size	real_salary, 4
real_salary:
	.zero	4
	.globl	increasing
	.section	.rodata
	.align 4
	.type	increasing, @object
	.size	increasing, 4
increasing:
	.long	1000
	.align 8
.LC0:
	.string	"please enter your expected salary"
.LC1:
	.string	"%d"
.LC2:
	.string	"please enter your real salary"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	expected_salary(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	real_salary(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	$1000, %edx
	movl	real_salary(%rip), %ecx
	movl	expected_salary(%rip), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	print_data@PLT
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
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
