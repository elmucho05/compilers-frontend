	.text
	.file	"inssort2.ll"
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0                          # -- Begin function inssort
.LCPI0_0:
	.quad	0x4024000000000000              # double 10
.LCPI0_1:
	.quad	0xbff0000000000000              # double -1
.LCPI0_2:
	.quad	0x3ff0000000000000              # double 1
	.text
	.globl	inssort
	.p2align	4, 0x90
	.type	inssort,@function
inssort:                                # @inssort
	.cfi_startproc
# %bb.0:                                # %entry
	movabsq	$4607182418800017408, %rax      # imm = 0x3FF0000000000000
	movq	%rax, -24(%rsp)
	movsd	.LCPI0_0(%rip), %xmm0           # xmm0 = mem[0],zero
	movq	A@GOTPCREL(%rip), %rax
	movsd	.LCPI0_1(%rip), %xmm1           # xmm1 = mem[0],zero
	movsd	.LCPI0_2(%rip), %xmm2           # xmm2 = mem[0],zero
	jmp	.LBB0_1
	.p2align	4, 0x90
.LBB0_6:                                # %endloop
                                        #   in Loop: Header=BB0_1 Depth=1
	movsd	-16(%rsp), %xmm3                # xmm3 = mem[0],zero
	addsd	%xmm2, %xmm3
	cvttsd2si	%xmm3, %ecx
	movsd	-8(%rsp), %xmm3                 # xmm3 = mem[0],zero
	movslq	%ecx, %rcx
	movsd	%xmm3, (%rax,%rcx,8)
	movsd	-24(%rsp), %xmm3                # xmm3 = mem[0],zero
	addsd	%xmm2, %xmm3
	movsd	%xmm3, -24(%rsp)
.LBB0_1:                                # %condeval
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
	movsd	-24(%rsp), %xmm3                # xmm3 = mem[0],zero
	ucomisd	%xmm0, %xmm3
	jae	.LBB0_7
# %bb.2:                                # %forloop
                                        #   in Loop: Header=BB0_1 Depth=1
	movsd	-24(%rsp), %xmm3                # xmm3 = mem[0],zero
	cvttsd2si	%xmm3, %ecx
	movslq	%ecx, %rcx
	movsd	(%rax,%rcx,8), %xmm4            # xmm4 = mem[0],zero
	movsd	%xmm4, -8(%rsp)
	addsd	%xmm1, %xmm3
	.p2align	4, 0x90
.LBB0_3:                                # %condeval4
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movsd	%xmm3, -16(%rsp)
	movsd	-16(%rsp), %xmm3                # xmm3 = mem[0],zero
	ucomisd	%xmm3, %xmm1
	jae	.LBB0_6
# %bb.4:                                # %condeval4
                                        #   in Loop: Header=BB0_3 Depth=2
	movsd	-8(%rsp), %xmm4                 # xmm4 = mem[0],zero
	cvttsd2si	%xmm3, %ecx
	movslq	%ecx, %rcx
	ucomisd	(%rax,%rcx,8), %xmm4
	jae	.LBB0_6
# %bb.5:                                # %forloop12
                                        #   in Loop: Header=BB0_3 Depth=2
	movsd	-16(%rsp), %xmm3                # xmm3 = mem[0],zero
	movapd	%xmm3, %xmm4
	addsd	%xmm2, %xmm4
	cvttsd2si	%xmm4, %ecx
	cvttsd2si	%xmm3, %edx
	movslq	%edx, %rdx
	movsd	(%rax,%rdx,8), %xmm4            # xmm4 = mem[0],zero
	movslq	%ecx, %rcx
	movsd	%xmm4, (%rax,%rcx,8)
	subsd	%xmm2, %xmm3
	jmp	.LBB0_3
.LBB0_7:                                # %endloop27
	xorpd	%xmm0, %xmm0
	retq
.Lfunc_end0:
	.size	inssort, .Lfunc_end0-inssort
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0                          # -- Begin function main
.LCPI1_0:
	.quad	0x4024000000000000              # double 10
.LCPI1_1:
	.quad	0x3ff0000000000000              # double 1
	.text
	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -24
	.cfi_offset %rbp, -16
	callq	timek@PLT
	movsd	%xmm0, 16(%rsp)
	callq	randinit@PLT
	movq	$0, (%rsp)
	movq	A@GOTPCREL(%rip), %rbx
	.p2align	4, 0x90
.LBB1_1:                                # %condeval
                                        # =>This Inner Loop Header: Depth=1
	movsd	(%rsp), %xmm0                   # xmm0 = mem[0],zero
	ucomisd	.LCPI1_0(%rip), %xmm0
	jae	.LBB1_3
# %bb.2:                                # %forloop
                                        #   in Loop: Header=BB1_1 Depth=1
	cvttsd2si	(%rsp), %ebp
	callq	randk@PLT
	movslq	%ebp, %rax
	movsd	%xmm0, (%rbx,%rax,8)
	cvttsd2si	(%rsp), %eax
	cltq
	movsd	(%rbx,%rax,8), %xmm0            # xmm0 = mem[0],zero
	xorps	%xmm1, %xmm1
	callq	printval@PLT
	movsd	(%rsp), %xmm0                   # xmm0 = mem[0],zero
	addsd	.LCPI1_1(%rip), %xmm0
	movsd	%xmm0, (%rsp)
	jmp	.LBB1_1
.LBB1_3:                                # %endloop
	xorpd	%xmm0, %xmm0
	movsd	.LCPI1_1(%rip), %xmm1           # xmm1 = mem[0],zero
	callq	printval@PLT
	callq	inssort@PLT
	movq	$0, 8(%rsp)
	.p2align	4, 0x90
.LBB1_4:                                # %condeval12
                                        # =>This Inner Loop Header: Depth=1
	movsd	8(%rsp), %xmm0                  # xmm0 = mem[0],zero
	ucomisd	.LCPI1_0(%rip), %xmm0
	jae	.LBB1_6
# %bb.5:                                # %forloop15
                                        #   in Loop: Header=BB1_4 Depth=1
	cvttsd2si	8(%rsp), %eax
	cltq
	movsd	(%rbx,%rax,8), %xmm0            # xmm0 = mem[0],zero
	xorps	%xmm1, %xmm1
	callq	printval@PLT
	movsd	8(%rsp), %xmm0                  # xmm0 = mem[0],zero
	addsd	.LCPI1_1(%rip), %xmm0
	movsd	%xmm0, 8(%rsp)
	jmp	.LBB1_4
.LBB1_6:                                # %endloop23
	xorpd	%xmm0, %xmm0
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	A,@object                       # @A
	.comm	A,80,16
	.section	".note.GNU-stack","",@progbits
