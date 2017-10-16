.orig x40

	.fill x5000

.end

.orig x3000

	; This is main. It is perfect and should not be modified.

	AND R0, R0, 0
	ADD R0, R0, 1
	ADD R1, R0, 1
	ADD R2, R0, 2
	ADD R3, R0, 3
	ADD R4, R0, 4
	ADD R5, R0, 5
	ADD R6, R0, 6

	TRAP x40

	HALT ; After halting, the registers should still contain 1, 2, 3, 4, 5, 6, 7.

.end

.orig x5000
	ST R0, BACKR0
	ST R1, BACKR1
	ST R2, BACKR2
	ST R3, BACKR3
	ST R4, BACKR4
	ST R5, BACKR5
	ST R6, BACKR6
	ST R7, BACKR7
LOOP    GETC ;R0 now has the chacter (1.do not need to change character 2.lowercase it 3.'\n'
	ADD R1, R0, #-10 ;R1 has end of line checker
	BRz END
	ADD R1, R1, #-15
	ADD R1, R1, #-15
	ADD R1, R1, #-15
	ADD R1, R1, #-10 ;R1 has upper case checker
	BRzp CHECK
	BRn PRINT
CHECK	ADD R1, R1, #-15
	ADD R1, R1, #-10 ;R1 has upper case checker (upper bound)
	BRnz UPPER
	BRp PRINT
UPPER	ADD R0, R0, #15
	ADD R0, R0, #15
	ADD R0, R0, #2 ;R0 has the upper to lower letter
PRINT	OUT
	BR LOOP
END	LD R0, BACKR0
	LD R1, BACKR1
	LD R2, BACKR2
	LD R3, BACKR3
	LD R4, BACKR4
	LD R5, BACKR5
	LD R6, BACKR6
	LD R7, BACKR7
	RET

; Some example .fills showing how to .fill ASCII character values more easily. Replace these with whatever you want.

BACKR0	.fill x0
BACKR1	.fill x0
BACKR2	.fill x0
BACKR3	.fill x0
BACKR4	.fill x0
BACKR5	.fill x0
BACKR6	.fill x0
BACKR7	.fill x0
NEWLINE .fill '\n'
Z	.fill 'Z'
A       .fill 'A'
a       .fill 'a'

.end

