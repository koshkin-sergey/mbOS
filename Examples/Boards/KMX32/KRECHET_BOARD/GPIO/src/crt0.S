/*
 Let make minimal init code to initialise the KM32 model.
 This code should init programm stack for GCC and call 
 function "main" - the entry point to test.
*/

/*
 0x0000 0000   CPU get first command from this address
 Jump to init code to initialise the KM32 proc.
*/
/*============================================================================*/

//#define FPGA_JTAG

	.section .init
	.global _entry
_entry:
		jmp	_start
		jmp	irq_1
		jmp	irq_2
		jmp	irq_3
		jmp	irq_4
		jmp	irq_5
		jmp	irq_6
		jmp	irq_7
		jmp	irq_8
		jmp	irq_9
		jmp	irq_10
		jmp	irq_11
		jmp	irq_12
		jmp	irq_13
		jmp	irq_14
		jmp	irq_15
		jmp	irq_16
		jmp	irq_17
		jmp	irq_18
		jmp	irq_19
		jmp	irq_20
		jmp	irq_21
		jmp	irq_22
		jmp	irq_23
		jmp	irq_24
		jmp	irq_25
		jmp	irq_26
		jmp	irq_27
		jmp	irq_28
		jmp	irq_29
		jmp	irq_30
		jmp	irq_31
		jmp	irq_32
		jmp	irq_33
		jmp	irq_34
		jmp	irq_35
		jmp	irq_36
		jmp	irq_37
		jmp	irq_38
		jmp	irq_39
		jmp	irq_40
		jmp	irq_41
		jmp	irq_42
		jmp	irq_43
		jmp	irq_44
		jmp	irq_45
		jmp	irq_46
		jmp	irq_47
		jmp	irq_48
		jmp	irq_49
		jmp	irq_50
		jmp	irq_51
		jmp	irq_52
		jmp	irq_53
		jmp	irq_54
		jmp	irq_55
		jmp	irq_56
		jmp	irq_57
		jmp	irq_58
		jmp	irq_59
		jmp	irq_60
		jmp	irq_61
		jmp	irq_62
		jmp	irq_63

	.org	0x100
	.global _start
_start:
    cst 	0x10
	ldrsl	PRW,	0
;	ldrh	flbr,	hi(__auto_flbr)
;	ldrl	flbr,	lo(__auto_flbr)
;	ldrl	flbr,	0x400 /*adr(__auto_flbr)*/
/*	ldrl	flbr,	0x400*/
/*	ldrl	CMBR,	adr(__auto_cmbr)
	ldrl	DMBR,	adr(__auto_dmbr)*/
	ldrzs	FA,	fa_base
	ldrzs	FB,	fb_base
	ldrsl	CONF, 0
	ldrsh	CONF, 45
	ldrsl	DP1ID,	0x1
	ldrsl	DP2ID,	0x1
	movl	c7,	lit(__stack - 4) /* avoid dp auto increment border condition bug */
/*	ldrl	ISP,	0 */

;-------------------------------------------------------------------------------
#ifdef FPGA_JTAG
	ldrsl	PRW,	3
	ldrl	r30,	0
	ldrsl	PRW,	0
#endif
/* Copy data section to ram */
	movl	a0,	hi(_sdata)
	smovl	a0,	lo(_sdata)
	
	movl	a1,	hi(_edata)
	smovl	a1,	lo(_edata)
				
	;If size of DATA is 0 (zero) nothing should be done.
	cmp	a0,	a1
	beq	1$

	mov	dp1,	a0
		
	sub	a1,	a0
	shr	a1,	2

	movl	a0,	hi(__data_image)
	smovl	a0,	lo(__data_image)
	mov	c2,	a0
	nop

	mtprs	smc,	a1
	sst	0x40
	ldd	(dp1)+,	(c2)+

/*
3$:
	ldw	a0,	(dp2)+
	stw	(dp1)+,	a0
	dec	a1
	bne	3$
*/
1$:

;-------------------------------------------------------------------------------
/* Clear the bss section */
	movl	a0, 	hi(_sbss)
	smovl	a0, 	lo(_sbss)
	
	movl	a1, 	hi(_ebss)
	smovl	a1, 	lo(_ebss)
		
	;If size of BSS is 0 (zero) nothing should be done.
	cmp	a0,	a1
	beq	2$

	mov	dp1, 	a0
	sub	a1,	a0
	shr	a1,	2
	movl 	a0, 	0

	mtprs	smc,	a1
	sst	0x40
	mov	(dp1)+,	a0
2$:

;-------------------------------------------------------------------------------

/* Call constructors */
	movl	c0, 	hi(__ctors_start)
	smovl	c0, 	lo(__ctors_start)
	
	movl	c1, 	hi(__ctors_end)
	smovl	c1, 	lo(__ctors_end)
		
	;If size of CTORS is 0 (zero) nothing should be done.
	cmp	c0,	c1
	beq	4$

5$:
	subls	c1,	4
	mov	c2, 	c1
	nop
	ldd	a0,	(c2)
	mov	c2,	a0
	nop
	ijsr	c2
	cmp	c0,	c1
	bne	5$
4$:


/* Call the main function */
	jsr	main

	mov	b0,	a0
/* Call destructors */
	movl	c0, 	hi(__dtors_start)
	smovl	c0, 	lo(__dtors_start)
	
	movl	c1, 	hi(__dtors_end)
	smovl	c1, 	lo(__dtors_end)
		
	;If size of DTORS is 0 (zero) nothing should be done.
	cmp	c0,	c1
	beq	6$

7$:
	mov	c2, 	c0
	nop
	ldd	a0,	(c2)
	mov	c2,	a0
	nop
	ijsr	c2
	addls	c0,	4
	cmp	c0,	c1
	bne	7$
6$:

	mov	a0,	b0
/* Stop execution */	
#ifdef FPGA_JTAG
	ldrsl	PRW,	3
	movl	a1, 	hi(0xfade0000)
	smovl	a1, 	lo(0xfade0000)
	or	a1,	a0
	mtpr	r30,	a1
	ldrsl	PRW,	0
#endif
	stop
	br	.-2

	.size	_start, . - _start


	.text
	.align 1
	.global _exit
	.type _exit, @function
_exit:
#ifdef FPGA_JTAG
	ldrsl	PRW,	3
	movl	a1, 	hi(0xfade1000)
	smovl	a1, 	lo(0xfade1000)
	or	a1,	a0
	mtpr	r30,	a1
	ldrsl	PRW,	0
#endif
    	stop
	br	.-2
    	
    	.size _exit, .- _exit

	.align 1
	.global abort
	.type abort, @function
abort:
#ifdef FPGA_JTAG
/*	mfpr	a0,	err*/
	movl	a0,	0x1
	ldrsl	PRW,	3
	movl	a1, 	hi(0xfade2000)
	smovl	a1, 	lo(0xfade2000)
	or	a1,	a0
	mtpr	r30,	a1
	ldrsl	PRW,	0
#else
	movl	a0,	0x1
#endif
    	stop
	br	.-2
    	
    	.size abort, .- abort

	.section	.noinit
	.align	4
fa_base:
	.fill	8, 4, 0
fb_base:
	.fill	8, 4, 0
