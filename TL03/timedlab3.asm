;;==================================
;; Timed Lab 3 (Fall 2017)
;;
;; Name: Jingbo Wang
;;===================================
;;
;; Write a program that compares two strings
;; (STR1 and STR2) by their alphabetic order.
;; Store the result in ANS
;;

.orig x3000

	LD R0, STR1	;R0 stores STR1_ADDR
	LD R1, STR2	;R1 stores STR2_ADDR
LOOP	LDR R2, R0, 0	;R2 stores char1
	LDR R3, R1, 0	;R3 stores char2
	BRz EQUAL
	NOT R4, R3	
	ADD R4, R4, 1	;R4 stores -char2
	ADD R4, R2, R4	;R4 stores char1-char2
	BRp ONE
	BRn NEG
	ADD R0, R0, 1	;next char1
	ADD R1, R1, 1	;next char2
	BR LOOP
ONE	AND R0, R0, 0	;clear R0
	ADD R0, R0, 1	;R0=1
	ST R0, ANS
	HALT
NEG	AND R0, R0, 0	;clear R0
	ADD R0, R0, -1	;R0=-1
	ST R0, ANS
	HALT
EQUAL	AND R0, R0, 0	;clear R0
	ST R0, ANS
	HALT

STR1 .fill x5000
STR2 .fill x5050
ANS .fill -10   ; store result of comparison in ANS
.end

;; This is where the first element of the first string is stored
.orig x5000
.stringz "bats"
.end

;; This is where the first element of the second string is stored
.orig x5050
.stringz "cats"
.end
