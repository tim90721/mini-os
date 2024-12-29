#define SIZE	5

	.data

	.align 3	// align address to 8-byte
src:			// source array, size = 5 integer
	.int 1
	.int 2
	.int 3
	.int 4
	.int 5

	.align 3
dst:			// align address to 8-byte
	.rept 5		// destination array, size = 5 integer
	.int 0
	.endr

	.text
	.global _start
_start:
	ldr	x0,	=src		// source address
	ldr	x1,	=dst		// destination address
	ldr	x2,	=SIZE		// size

double_word_copy:
1:
	// copy by double word first
	cmp	x2,	#2
	b.lt	1f
	ldr	x3,	[x0],	#8
	str	x3,	[x1],	#8
	sub	x2,	x2,	#2	// size -= 2
	b	1b

1:
	// copy by word
	cmp	x2,	#0
	b.eq	stop
	ldr	w3,	[x0],	#4
	str	w3,	[x1],	#4
	sub	x2,	x2,	#1	// size -= 1
	b	1b

stop:
1:
	b 1b
