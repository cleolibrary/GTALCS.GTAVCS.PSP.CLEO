.text

#------------------------------------- call func with context -----------------------------------

	.align 2
	.global	asm_call
	.code	16
	.thumb_func
	.type	asm_call, %function
asm_call:
	push 	{R0-R7, LR}
	mov		R6, R0
	mov		R7, R1

	ldr  	R1, [R0, #0]
	push	{R1}
	ldr  	R1, [R0, #4]
	push	{R1}
	ldr  	R1, [R0, #8]
	push	{R1}
	ldr  	R1, [R0, #12]
	push	{R1}
	ldr  	R1, [R0, #16]
	push	{R1}
	ldr  	R1, [R0, #20]
	push	{R1}
	pop		{R5}
	pop		{R4}
	pop		{R3}
	pop		{R2}
	pop		{R1}
	pop		{R0}

	blx		R7
	str  	R0, [R6, #0]

	pop  	{R0-R7, PC}


