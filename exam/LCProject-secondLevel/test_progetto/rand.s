	.text
	.file	"rand.ll"
	.globl	randk                           # -- Begin function randk
	.p2align	4, 0x90
	.type	randk,@function
randk:                                  # @randk
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	movq	a@GOTPCREL(%rip), %rax
	movsd	(%rax), %xmm0                   # xmm0 = mem[0],zero
	movq	seed@GOTPCREL(%rip), %rbx
	mulsd	(%rbx), %xmm0
	movsd	%xmm0, 8(%rsp)                  # 8-byte Spill
	movsd	%xmm0, 16(%rsp)
	movq	m@GOTPCREL(%rip), %r14
	movsd	(%r14), %xmm1                   # xmm1 = mem[0],zero
	movsd	%xmm1, (%rsp)                   # 8-byte Spill
	divsd	%xmm1, %xmm0
	callq	floor@PLT
	mulsd	(%rsp), %xmm0                   # 8-byte Folded Reload
	movsd	8(%rsp), %xmm1                  # 8-byte Reload
                                        # xmm1 = mem[0],zero
	subsd	%xmm0, %xmm1
	movsd	%xmm1, (%rbx)
	divsd	(%r14), %xmm1
	movapd	%xmm1, %xmm0
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	randk, .Lfunc_end0-randk
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0                          # -- Begin function randinit
.LCPI1_0:
	.quad	0x41dfffffffc00000              # double 2147483647
	.text
	.globl	randinit
	.p2align	4, 0x90
	.type	randinit,@function
randinit:                               # @randinit
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movsd	%xmm0, 8(%rsp)                  # 8-byte Spill
	movsd	%xmm0, 16(%rsp)
	movq	a@GOTPCREL(%rip), %rax
	movabsq	$4670373825949466624, %rcx      # imm = 0x40D0804000000000
	movq	%rcx, (%rax)
	movq	m@GOTPCREL(%rip), %rax
	movabsq	$4746794007244308480, %rcx      # imm = 0x41DFFFFFFFC00000
	movq	%rcx, (%rax)
	divsd	.LCPI1_0(%rip), %xmm0
	callq	floor@PLT
	mulsd	.LCPI1_0(%rip), %xmm0
	movsd	8(%rsp), %xmm1                  # 8-byte Reload
                                        # xmm1 = mem[0],zero
	subsd	%xmm0, %xmm1
	movq	seed@GOTPCREL(%rip), %rax
	movsd	%xmm1, (%rax)
	xorpd	%xmm0, %xmm0
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	randinit, .Lfunc_end1-randinit
	.cfi_endproc
                                        # -- End function
	.type	seed,@object                    # @seed
	.comm	seed,8,8
	.type	a,@object                       # @a
	.comm	a,8,8
	.type	m,@object                       # @m
	.comm	m,8,8
	.section	".note.GNU-stack","",@progbits
