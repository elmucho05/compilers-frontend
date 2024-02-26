	.text
	.file	"eqn2.ll"
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0                          # -- Begin function eqn2
.LCPI0_0:
	.quad	0xc010000000000000              # double -4
.LCPI0_1:
	.quad	0x3ff0000000000000              # double 1
	.text
	.globl	eqn2
	.p2align	4, 0x90
	.type	eqn2,@function
eqn2:                                   # @eqn2
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$88, %rsp
	.cfi_def_cfa_offset 96
	movsd	%xmm0, (%rsp)
	movsd	%xmm1, 8(%rsp)
	movsd	%xmm2, 24(%rsp)
	mulsd	%xmm1, %xmm1
	mulsd	.LCPI0_0(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, 16(%rsp)
	xorpd	%xmm1, %xmm1
	ucomisd	%xmm1, %xmm0
	jae	.LBB0_5
# %bb.1:                                # %trueexp
	xorpd	%xmm0, %xmm0
	subsd	16(%rsp), %xmm0
	ucomisd	%xmm1, %xmm0
	jb	.LBB0_3
# %bb.2:
	xorps	%xmm1, %xmm1
	sqrtsd	%xmm0, %xmm1
	jmp	.LBB0_4
.LBB0_5:                                # %falseexp
	ucomisd	16(%rsp), %xmm1
	je	.LBB0_6
# %bb.8:                                # %falseexp33
	movsd	16(%rsp), %xmm0                 # xmm0 = mem[0],zero
	ucomisd	%xmm1, %xmm0
	jb	.LBB0_10
# %bb.9:
	sqrtsd	%xmm0, %xmm0
	jmp	.LBB0_11
.LBB0_3:                                # %call.sqrt
	callq	sqrt@PLT
	movapd	%xmm0, %xmm1
.LBB0_4:                                # %trueexp.split
	movsd	%xmm1, 32(%rsp)
	xorpd	%xmm0, %xmm0
	subsd	8(%rsp), %xmm0
	movsd	(%rsp), %xmm2                   # xmm2 = mem[0],zero
	addsd	%xmm2, %xmm2
	divsd	%xmm2, %xmm0
	movsd	%xmm0, 40(%rsp)
	divsd	%xmm2, %xmm1
	movsd	%xmm1, 48(%rsp)
	xorpd	%xmm2, %xmm2
	jmp	.LBB0_12
.LBB0_6:                                # %trueexp25
	xorpd	%xmm0, %xmm0
	subsd	8(%rsp), %xmm0
	movsd	(%rsp), %xmm1                   # xmm1 = mem[0],zero
	addsd	%xmm1, %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, 56(%rsp)
	xorpd	%xmm1, %xmm1
	xorpd	%xmm2, %xmm2
	jmp	.LBB0_12
.LBB0_10:                               # %call.sqrt1
	callq	sqrt@PLT
	xorpd	%xmm1, %xmm1
.LBB0_11:                               # %falseexp33.split
	movsd	%xmm0, 64(%rsp)
	subsd	8(%rsp), %xmm1
	movapd	%xmm1, %xmm3
	addsd	%xmm0, %xmm3
	movsd	(%rsp), %xmm2                   # xmm2 = mem[0],zero
	addsd	%xmm2, %xmm2
	divsd	%xmm2, %xmm3
	movsd	%xmm3, 72(%rsp)
	subsd	%xmm0, %xmm1
	divsd	%xmm2, %xmm1
	movsd	%xmm1, 80(%rsp)
	movsd	.LCPI0_1(%rip), %xmm2           # xmm2 = mem[0],zero
	movapd	%xmm3, %xmm0
.LBB0_12:                               # %endcond54
	callq	printval@PLT
	addq	$88, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	eqn2, .Lfunc_end0-eqn2
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
