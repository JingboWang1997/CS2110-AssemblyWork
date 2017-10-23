;;===============================
;; CS 2110 Fall 2017
;; Homework 7 - Functions & Recursion
;; Name:
;;===============================

; DO NOT REMOVE THIS LINE
;@plugin filename=lc3_udiv vector=x80

.orig x3000
    LD R6, STACK   
    ADD  R6, R6, -2      ; Add arguments onto stack
    LD   R0, A		 ; Push args onto stack
    STR  R0, R6, 0
    LD   R0, B
    STR  R0, R6, 1
    JSR  GCD             ; Call GCD
    LDR  R0, R6, 0       ; R0 = return value
    ST   R0, ANSWER	 ; ANSWER = return value
    ADD  R6, R6, 3       ; Pop off return value and 2 args

    HALT


A       .fill 30
B       .fill 29
ANSWER  .blkw 1
STACK   .fill xF000



GCD
	;stack frame
	ADD R6, R6, -3 ; Allocate space for core stack frame (RV, RA, OldFP)
	STR R7, R6, 1  ; Save the Return Address
	STR R5, R6, 0  ; Save old FP
	ADD R5, R6, -1 ; Set new FP
	;save registers
	ADD R6, R6, -3  ; Make space to save R0-R2
    	STR R0, R5, 0   ; Save R0 as 1st local
    	STR R1, R5, -1  ; Save R1 as 2nd local
	STR R2, R5, -2  ; Save R2 as 3rd local
	;get args off the stack
	LDR R0, R5, #4 ;R0 stores A
	LDR R1, R5, #5 ;R1 stores B
	LDR R2, R5, #5 ;R2 stores B
	;operation
	UDIV
	ADD R1, R1, 0 ;get R1 in cc
	BRz FINISH
	BR RECURSE
RECURSE	ADD  R6, R6, -2      ; Add arguments onto stack
	STR  R2, R6, 0
	STR  R1, R6, 1
	JSR  GCD              ; Call GCD
	LDR  R0, R6, 0       ; R0 = return value
	ADD  R6, R6, 3       ; Pop off return value and 2 args
	BR LAST
FINISH	ADD R0, R2, 0
	;save result in RV
LAST	STR R0, R5, #3 ;store answer into return value
	;restore register
	LDR R0, R5, 0 ;load R0 back
	LDR R1, R5, -1 ;load R1 back
	LDR R2, R5, -2 ;load R2 back
	ADD R6, R6, 3 ;tear down the top
	;tear down the rest
	LDR R7, R5, 2  ; Restore return address
	ADD R6, R5, 1  ; Move SP to old FP
   	LDR R5, R5, 1  ; Resore old FP
    	ADD R6, R6, 2  ; Move SP to point at the return value
    	RET

.end
