#define VALUE	0x20

	.data				// data section
	.align 3			// align to 8-byte address (2^3)

some_data:
	.rept 4				// create 3-byte values on data section
	.byte 8				// each value is 8
	.endr

other_space:
	.rept 8
	.byte 0
	.endr

some_space:
	.rept 10
	.byte 0
	.endr

	.align 5
test_data1:
	.int 0x10101010
test_data2:
	.int 0x20202020
test_data3:
	.int 0x30303030

test_space:
	.rept 3
	.int 0
	.endr

dummy_space:
	.rept 20
	.int 0
	.endr

	.text				// equals to .section .text
					// .section can be followed by
					// additional flags
					// a: the section is allocatable
					// x: the section is executable
					// w: the section is writable
					// S: the section contains
					//    null-terminated strings
					// for example
					// .section .init,"ax"
	.global _start
_start:
ldr_basic:
	ldr	x0,	=VALUE		// pseudo instruction, load VALUE's
					// value to x0
	ldr	x0,	=some_data	// load address from "some_data" label
					// some_data points to data section
					// 0x44000000 which has 3 bytes and
					// each byte value is 8
					// pseudo instruction, load some_data's
					// address to x0
	ldr	w1,	[x0]		// load 32-bit data from some_data's
					// address
	ldrh	w2,	[x0]		// load 16-bit data from some_data's
					// address
	ldrb	w3,	[x0]		// load 8-bit data from some_data's
					// address

str_basic:
	ldr	x4,	=some_space

	strb	w3,	[x4]
	strh	w2,	[x4, #2]
	str	w1,	[x4, #4]

	mov	x30,	#1
	str	x1,	[x0, x30, LSL #3]	// store x1's value to address
						// x0 + (x30 << 3)
						// shift value must be 0 or 3

addr_indexing:
	ldr	x5,	=test_data1
	ldr	w6,	[x5, #4]!	// pre-indexing
					// add 4 to x5 then read the value at
					// address x5 to w10
	ldr	w7,	[x5], #4	// post-indexing
					// read the value at address x5 to x10
					// then add 4 to x5

	ldr	x8,	=test_space
	str	w6,	[x8, #4]!	// pre-indexing
	str	w6,	[x8, #4]!	// pre-indexing
	str	w6,	[x8], #4	// post-indexing

ldp_stp:
	ldr	x9,	=dummy_space
	mov	w10,	#1
	mov	w11,	#2

	stp	w10,	w11,	[x9]		// store w10 to address x9
						// store w11 to address x9 + 8
	stp	w10,	w11,	[x9, #8]!	// pre-indexing
						// x9 += 8
						// store w10 to address x9
						// store w11 to address x9 + 8

	mov	w10,	#3
	mov	w11,	#4
	stp	w10,	w11,	[x9], #8

	ldr	x9,	=dummy_space
	ldp	w10,	w11,	[x9]
	ldp	w10,	w11,	[x9, #8]!

stop:
	b stop

	.end
