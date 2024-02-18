	.text
	.file	"fibonacciIt.ll"
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0                          # -- Begin function fibo
.LCPI0_0:
	.quad	0x3ff0000000000000              # double 1
	.text
	.globl	fibo
	.p2align	4, 0x90
	.type	fibo,@function
fibo:                                   # @fibo
	.cfi_startproc
# %bb.0:                                # %entry
	movsd	%xmm0, -16(%rsp)
	movq	$0, -24(%rsp)
	movabsq	$4607182418800017408, %rax      # imm = 0x3FF0000000000000
	movq	%rax, -40(%rsp)
	movq	%rax, -32(%rsp)
	movsd	.LCPI0_0(%rip), %xmm0           # xmm0 = mem[0],zero
	.p2align	4, 0x90
.LBB0_1:                                # %condeval
                                        # =>This Inner Loop Header: Depth=1
	movsd	-32(%rsp), %xmm1                # xmm1 = mem[0],zero
	ucomisd	-16(%rsp), %xmm1
	jae	.LBB0_3
# %bb.2:                                # %forloop
                                        #   in Loop: Header=BB0_1 Depth=1
	movsd	-40(%rsp), %xmm1                # xmm1 = mem[0],zero
	movsd	%xmm1, -8(%rsp)
	movsd	-24(%rsp), %xmm2                # xmm2 = mem[0],zero
	addsd	%xmm1, %xmm2
	movsd	%xmm2, -40(%rsp)
	movsd	%xmm1, -24(%rsp)
	movsd	-32(%rsp), %xmm1                # xmm1 = mem[0],zero
	addsd	%xmm0, %xmm1
	movsd	%xmm1, -32(%rsp)
	jmp	.LBB0_1
.LBB0_3:                                # %endloop
	movsd	-40(%rsp), %xmm0                # xmm0 = mem[0],zero
	retq
.Lfunc_end0:
	.size	fibo, .Lfunc_end0-fibo
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
