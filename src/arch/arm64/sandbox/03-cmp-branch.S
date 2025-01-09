// Branch instructions
// B      <label>:	branch to a specific label where label is in PC +- 128MB
// B.cond <label>:	branch to a specific label where label is in PC +- 1MB
// BL     <label>:	branch and link to a specific label where label is in
//			PC +- 128MB. link->store next instruction's address to
//			LR (link register, x30)
// BR     <Xm>:		branch to the address stored in Xm
// BLR    <Xm>:		branch and link to the address stored in Xm

	.align 5
	.text
	.global _start
_start:
cmp_test:			// pseudo instruction with subs
	mov	x0,	#10	// subs xzr, xm, xn
	mov	x1,	#20	// compare xm with xn
	cmp	x0,	x1
	b.lt	cmn_test
	mov	x0,	#20
	mov	x1,	#10

cmn_test:			// pseudo instruction with adds
	mov	x2,	#10	// adds xzr, xm, xn
	mov	x3,	#20	// compare xm with xn's 2's complement
	cmn	x2,	x3
	b.gt	csel_test
	mov	x2,	#20
	mov	x3,	#10

csel_test:					// csel xd, xm, xn, cond
	mov	x4,	#10			// if cond is true
	mov	x5,	#20			//	set xd to xm
	cmp	x4,	x5			// otherwise,
	csel	x6,	x4,	x5,	gt	//	set xd to xn
	csel	x7,	x4,	x5,	lt

cset_test:					// cset xd, cond
	mov	x8,	#10			// if cond is true
	mov	x9,	#10			//	set xd to 1
	cmp	x8,	x9			// otherwise,
	cset	x10,	eq			//	set xd to 0
	cset	x11,	ne

csinc_test:					// csinc xd, xm, xn, cond
	mov	x12,	#10			// if cond is true
	mov	x13,	#20			//	set xd to xm
	cmp	x12,	x13			// otherwise,
	csinc	x14,	x12,	x13,	gt	//	set xd to xn + 1
	csinc	x15,	x12,	x13,	lt

cbz_test:					// cbz xm, <label>
	mov	x16,	#0			// branch to label if xm is 0
	cbz	x16,	cbnz_test		// label must be PC +- 1MB
	mov	x16,	#10

cbnz_test:
	mov	x17,	#10
	cbnz	x17,	tbz_test
	mov	x17,	#0

tbz_test:					// tbz xm, #imm, <label>
	mov	x18,	0xf0			// branch to label if xm's #imm
	tbz	x18,	#3,	tbnz_test	// equals to 0
	mov	x18,	#0

tbnz_test:
	mov	x19,	#0xf0
	tbnz	x19,	#4,	stop
	mov	x19,	#1

stop:
1:
	b 1b
