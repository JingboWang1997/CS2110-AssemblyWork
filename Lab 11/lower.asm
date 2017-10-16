.orig x40

	; TODO what goes here?

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

        ; TODO: What goes here?

	RET

; Some example .fills showing how to .fill ASCII character values more easily. Replace these with whatever you want.

NEWLINE .fill '\n'
Z	.fill 'Z'
A       .fill 'A'
a       .fill 'a'

.end

