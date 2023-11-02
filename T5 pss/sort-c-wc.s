	.file	"sort-c-wc.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	palabras
	.type	palabras, @function
palabras:
	lbu	a5,0(a0)
	beq	a5,zero,.L8
	li	a4,0
	li	a2,0
	li	a3,32
	li	a6,1
	li	a7,0
	j	.L4
.L14:
	beq	a4,zero,.L3
	addi	a2,a2,1
	mv	a4,a7
.L3:
	addi	a0,a0,1
	lbu	a5,0(a0)
	beq	a5,zero,.L2
.L4:
	beq	a5,a3,.L14
	mv	a4,a6
	j	.L3
.L8:
	li	a4,0
	li	a2,0
.L2:
	add	a0,a2,a4
	lbu	a5,0(a1)
	beq	a5,zero,.L10
	li	a4,0
	li	a2,0
	li	a3,32
	li	a6,1
	li	a7,0
	j	.L7
.L15:
	beq	a4,zero,.L6
	addi	a2,a2,1
	mv	a4,a7
.L6:
	addi	a1,a1,1
	lbu	a5,0(a1)
	beq	a5,zero,.L5
.L7:
	beq	a5,a3,.L15
	mv	a4,a6
	j	.L6
.L10:
	li	a4,0
	li	a2,0
.L5:
	add	a2,a2,a4
	sub	a0,a0,a2
	ret
	.size	palabras, .-palabras
	.align	2
	.globl	sort
	.type	sort, @function
sort:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	sw	s1,20(sp)
	sw	s2,16(sp)
	sw	s3,12(sp)
	sw	s4,8(sp)
	slli	s3,a1,2
	addi	s3,s3,-4
	add	s3,a0,s3
	bgeu	a0,s3,.L16
	mv	s4,a0
	mv	s0,a0
	j	.L20
.L18:
	sw	s2,0(s0)
	sw	s1,4(s0)
	mv	s0,s4
.L20:
	lw	s1,0(s0)
	lw	s2,4(s0)
	mv	a1,s2
	mv	a0,s1
	call	palabras
	bgt	a0,zero,.L18
	addi	s0,s0,4
	bgtu	s3,s0,.L20
.L16:
	lw	ra,28(sp)
	lw	s0,24(sp)
	lw	s1,20(sp)
	lw	s2,16(sp)
	lw	s3,12(sp)
	lw	s4,8(sp)
	addi	sp,sp,32
	jr	ra
	.size	sort, .-sort
	.ident	"GCC: () 11.1.0"
