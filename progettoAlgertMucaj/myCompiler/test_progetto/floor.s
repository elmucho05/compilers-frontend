	.text
	.file	"floor.ll"
	.globl	pow2                            # -- Begin function pow2
	.p2align	4, 0x90
	.type	pow2,@function
pow2:                                   # @pow2
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movsd	%xmm0, 16(%rsp)
	movsd	%xmm1, 8(%rsp)
	addsd	%xmm1, %xmm1
	ucomisd	%xmm1, %xmm0
	jae	.LBB0_2
# %bb.1:                                # %trueexp
	movsd	8(%rsp), %xmm0                  # xmm0 = mem[0],zero
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.LBB0_2:                                # %falseexp
	.cfi_def_cfa_offset 32
	movsd	16(%rsp), %xmm0                 # xmm0 = mem[0],zero
	movsd	8(%rsp), %xmm1                  # xmm1 = mem[0],zero
	addsd	%xmm1, %xmm1
	callq	pow2@PLT
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	pow2, .Lfunc_end0-pow2
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0                          # -- Begin function intpart
.LCPI1_0:
	.quad	0x3ff0000000000000              # double 1
	.text
	.globl	intpart
	.p2align	4, 0x90
	.type	intpart,@function
intpart:                                # @intpart
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movsd	%xmm0, (%rsp)
	movsd	%xmm1, 8(%rsp)
	xorpd	%xmm1, %xmm1
	ucomisd	.LCPI1_0(%rip), %xmm0
	xorpd	%xmm0, %xmm0
	jb	.LBB1_2
# %bb.1:                                # %falseexp
	movsd	(%rsp), %xmm0                   # xmm0 = mem[0],zero
	movsd	.LCPI1_0(%rip), %xmm1           # xmm1 = mem[0],zero
	callq	pow2@PLT
	xorpd	%xmm1, %xmm1
.LBB1_2:                                # %endcond
	movsd	%xmm0, 16(%rsp)
	ucomisd	%xmm1, %xmm0
	je	.LBB1_3
# %bb.4:                                # %falseexp8
	movsd	(%rsp), %xmm0                   # xmm0 = mem[0],zero
	movsd	16(%rsp), %xmm1                 # xmm1 = mem[0],zero
	subsd	%xmm1, %xmm0
	addsd	8(%rsp), %xmm1
	callq	intpart@PLT
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.LBB1_3:                                # %trueexp6
	.cfi_def_cfa_offset 32
	movsd	8(%rsp), %xmm0                  # xmm0 = mem[0],zero
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	intpart, .Lfunc_end1-intpart
	.cfi_endproc
                                        # -- End function
	.globl	floor                           # -- Begin function floor
	.p2align	4, 0x90
	.type	floor,@function
floor:                                  # @floor
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movsd	%xmm0, (%rsp)
	xorps	%xmm1, %xmm1
	callq	intpart@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	floor, .Lfunc_end2-floor
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
