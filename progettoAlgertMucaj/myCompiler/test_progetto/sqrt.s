	.text
	.file	"sqrt.ll"
	.globl	err                             # -- Begin function err
	.p2align	4, 0x90
	.type	err,@function
err:                                    # @err
	.cfi_startproc
# %bb.0:                                # %entry
	movsd	%xmm0, -16(%rsp)
	movsd	%xmm1, -8(%rsp)
	ucomisd	%xmm1, %xmm0
	jae	.LBB0_2
# %bb.1:                                # %trueexp
	movsd	-8(%rsp), %xmm0                 # xmm0 = mem[0],zero
	subsd	-16(%rsp), %xmm0
	retq
.LBB0_2:                                # %falseexp
	movsd	-16(%rsp), %xmm0                # xmm0 = mem[0],zero
	subsd	-8(%rsp), %xmm0
	retq
.Lfunc_end0:
	.size	err, .Lfunc_end0-err
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0                          # -- Begin function iterate
.LCPI1_0:
	.quad	0x4000000000000000              # double 2
	.text
	.globl	iterate
	.p2align	4, 0x90
	.type	iterate,@function
iterate:                                # @iterate
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movsd	%xmm0, 8(%rsp)
	movsd	%xmm1, (%rsp)
	movabsq	$4547007122018943789, %rax      # imm = 0x3F1A36E2EB1C432D
	movq	%rax, 32(%rsp)
	mulsd	%xmm1, %xmm1
	movsd	%xmm1, 16(%rsp)
	.p2align	4, 0x90
.LBB1_1:                                # %condeval
                                        # =>This Inner Loop Header: Depth=1
	movsd	32(%rsp), %xmm0                 # xmm0 = mem[0],zero
	movsd	%xmm0, 24(%rsp)                 # 8-byte Spill
	movsd	16(%rsp), %xmm0                 # xmm0 = mem[0],zero
	movsd	8(%rsp), %xmm1                  # xmm1 = mem[0],zero
	callq	err@PLT
	movsd	24(%rsp), %xmm1                 # 8-byte Reload
                                        # xmm1 = mem[0],zero
	ucomisd	%xmm0, %xmm1
	jae	.LBB1_3
# %bb.2:                                # %forloop
                                        #   in Loop: Header=BB1_1 Depth=1
	movsd	(%rsp), %xmm0                   # xmm0 = mem[0],zero
	movsd	8(%rsp), %xmm1                  # xmm1 = mem[0],zero
	divsd	%xmm0, %xmm1
	addsd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm0
	movsd	%xmm0, 16(%rsp)
	divsd	.LCPI1_0(%rip), %xmm1
	movsd	%xmm1, (%rsp)
	jmp	.LBB1_1
.LBB1_3:                                # %endloop
	movsd	(%rsp), %xmm0                   # xmm0 = mem[0],zero
	addq	$40, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	iterate, .Lfunc_end1-iterate
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0                          # -- Begin function sqrt
.LCPI2_0:
	.quad	0x3ff0000000000000              # double 1
.LCPI2_1:
	.quad	0x4000000000000000              # double 2
	.text
	.globl	sqrt
	.p2align	4, 0x90
	.type	sqrt,@function
sqrt:                                   # @sqrt
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rax
	.cfi_def_cfa_offset 16
	movapd	%xmm0, %xmm1
	movsd	%xmm0, (%rsp)
	movsd	.LCPI2_0(%rip), %xmm0           # xmm0 = mem[0],zero
	ucomisd	%xmm0, %xmm1
	je	.LBB2_5
# %bb.1:                                # %falseexp
	movsd	(%rsp), %xmm0                   # xmm0 = mem[0],zero
	ucomisd	.LCPI2_0(%rip), %xmm0
	jae	.LBB2_3
# %bb.2:                                # %trueexp4
	movsd	(%rsp), %xmm0                   # xmm0 = mem[0],zero
	movsd	.LCPI2_0(%rip), %xmm1           # xmm1 = mem[0],zero
	subsd	%xmm0, %xmm1
	jmp	.LBB2_4
.LBB2_3:                                # %falseexp7
	movsd	(%rsp), %xmm0                   # xmm0 = mem[0],zero
	movapd	%xmm0, %xmm1
	divsd	.LCPI2_1(%rip), %xmm1
.LBB2_4:                                # %endcond11
	callq	iterate@PLT
.LBB2_5:                                # %endcond11
	popq	%rax
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	sqrt, .Lfunc_end2-sqrt
	.cfi_endproc
                                        # -- End function
	.section	".note.GNU-stack","",@progbits
