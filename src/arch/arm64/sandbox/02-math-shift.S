// ARM64 updates some PSTATE status while some mathematical result occurred
// PSTATE.N: last instruction causes a negative value
// PSTATE.Z: last instruction causes a zero value
// PSTATE.C: last instruction causes an unsigned value overflow
// PSTATE.V: last instruction causes a signed value overflow
//
// There are several branch instructions use these flags to decide whether to
// jump to the specific address
//
// The basic branch instruction, b, can append different operand such as EQ, NE
// Following are several operands that can be appened to branch instruction
// operand	meaning				PSTATE.NZCV
// EQ:		equal				Z == 1
// NE:		not equal			Z == 0
// CS/HS:	unsigned overflow		C == 1
// CC/LO	no unsigned overflow		C == 0
// MI		negative value			N == 1
// PL		positive or zero		N == 0
// VS		signed overflow			V == 1
// VC		no signed overflow		V == 0
// HI		unsigned larger than		(C == 1) && (Z == 0)
// LS		unsigned less than or equal	(C == 0) || (Z == 1)
// GE		signed larger than or equal	N == V
// LT		signed less than		N != V
// GT		signed larger than		(N == V) && (Z == 0)
// LE		signed less than or equal	(N != V) || (Z == 1)
// AL/NV	execute branch anyway

	.text
	.global _start
_start:
adds_test:
	mrs	x1,	nzcv
	mov	x0,	0xffffffffffffffff
	adds	x0,	x0,	#2
	mrs	x1,	nzcv			// cause unsigned overflow
						// NZCV.C = 1

	mrs	x3,	nzcv
	mov	x2,	0xffffffffffffffff
	adds	x2,	x2,	#1
	mrs	x3,	nzcv			// cause unsigned overflow
						// and zero value
						// NZCV.Z = 1, NZCV.C = 1

adc_test:
	mrs	x5,	nzcv
	mov	x4,	0xffffffffffffffff
	mov	x5,	#2
	adc	x4,	x4,	x5	// x4 = x4 + x5 + C, if last inst causes
					// an unsigned overflow, the result will
					// be x4 + x5 + 1. As a result, in this
					// example, x4 will be 0x2
	mrs	x5,	nzcv		// last command does not affect nzcf

sub_test:
	adds	x0,	x0,	#0

	mrs	x7,	nzcv
	mov	x6,	#5
	sub	x6,	x6,	#3	// no nzcv flag is updated since
					// sub does not affect nzcf
	mrs	x7,	nzcv

subs_test:
	mov	x8,	#1
	subs	x8,	x8,	#3
	mrs	x9,	nzcv		// NZCV.N = 1 since a negative value
					// is generated

// cmp is a pseudo instruction which is equalled to subs
// cmp <xn>, <xm> eqauls to subs xzr, <xn>, <xm>
cmp_test:
	mov	x10,	#11
	mov	x11,	#11
	cmp	x10,	x11
	b.eq	1f

1:
	mov	x10,	#11
	mov	x11,	#12
	cmp	x10,	x11
	b.lt	1f

1:
	mov	x10,	#11
	mov	x11,	#10
	cmp	x10,	x11
	b.gt	1f

1:
shift_test:
	mov	x12,	#-2		// 0xfffffffffffffffe
	lsl	x13,	x12,	1	// 0xfffffffffffffffc
	lsr	x14,	x12,	1	// 0x7fffffffffffffff
	asr	x15,	x12,	1	// 0xffffffffffffffff
	ror	x16,	x12,	1	// 0x7fffffffffffffff

bic_test:
	mov	x17,	0xf0
	mov	x18,	0xffffffffffffffff
	bic	x19,	x18,	x17	// clear x18 based on bits set in x17

clz_test:
	clz	x20,	x17		// count how many 0 in front of the left
					// most 1

bfi_test:					// bfi xd, xm, #lsb, #width
						// set xd based on xm with
						// specified lsb to lsb + width
	ldr	x21,	=0x5a5a5a5a5a5a5a5a
	mov	x22,	0xffffffffffffffff
	bfi	x21,	x22,	#12,	#8	// 0x5a5a5a5a5a5ffa5a

ubfx_sbfx_test:					// ubfx xd, xm, #lsb, #width
						// retrieve xm's lsb to
						// lsb + width to xd
	ldr	x23,	=0xa5a5a5a5a5a5a5a5
	ubfx	x24,	x23,	#5,	#4	// 0xd
	sbfx	x25,	x23,	#5,	#6	// 0xffffffffffffffed

	.end
