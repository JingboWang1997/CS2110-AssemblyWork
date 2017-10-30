;;===============================
;; CS 2110 Fall 2017
;; Homework 7 - Functions & Recursion
;; Name: Jingbo Wang
;;===============================

; DO NOT REMOVE THIS LINE
;@plugin filename=lc3_udiv vector=x80

.orig x3000

;;=====================================
;; Call bin_search subroutine with correct arguments here
;;=====================================

	LD  R6, STACK        ; Initialize stack

	ADD R6, R6, -4  ; Add arguments onto stack
    	LD  R0, ARR_SIZE; Push args onto stack
    	STR R0, R6, 3	; size at the bottom
   	AND R0, R0, 0	; clear R0
	STR R0, R6, 2	; 0 above size
	LD  R0, TARGET	
	STR R0, R6, 1	; TARGET above 0
	LD  R0, ARR
	STR R0, R6, 0	; ARR above TARGET
	LD  R0, BIN_SEARCH_ADDR
	JSRR R0 			; call BIN_SEARCH
	LDR R0, R6, 0       ; R0 = return value
    	ST  R0, ANSWER	 ; ANSWER = return value
    	ADD R6, R6, 5       ; Pop off return value and 4 args

	HALT

ARR 				.fill x4000
ARR_SIZE 			.fill 9
TARGET 				.fill 11
ANSWER      		.blkw 1         ; Store ANSWER here
BIN_SEARCH_ADDR		.fill BIN_SEARCH
STACK       		.fill xF000


.end
;;=====================================
;; The array to be searched
;;=====================================

.orig x4000
.fill 3
.fill 5
.fill 6
.fill 6
.fill 8
.fill 10
.fill 11
.fill 50
.fill 52

.end
;;=====================================
;; Implement your bin_search subroutine here
;;=====================================

.orig x5000
BIN_SEARCH
;stack frame
	ADD R6, R6, -3 ; Allocate space for core stack frame (RV, RA, OldFP)
	STR R7, R6, 1  ; Save the Return Address
	STR R5, R6, 0  ; Save old FP
	ADD R5, R6, -1 ; Set new FP
;save registers
	ADD R6, R6, -5  ; Make space to save R0-R4
    	STR R0, R5, 0   ; Save R0 as 1st local
    	STR R1, R5, -1  ; Save R1 as 2nd local
	STR R2, R5, -2  ; Save R2 as 3rd local
	STR R3, R5, -3  ; Save R3 as 4th local
	STR R4, R5, -4  ; Save R4 as 5th local
;get args off the stack
	LDR R0, R5, #4 ;R0 stores ARR
	LDR R1, R5, #5 ;R1 stores TARGET
	LDR R2, R5, #6 ;R2 stores START
	LDR R3, R5, #7 ;R3 stores END
;operation
	NOT R4, R3	;
	ADD R4, R4, 1	;R4 = -END
	ADD R4, R2, R4	;R4 = START - END
	BRzp NOTFOUND
	NOT R0, R4
	ADD R0, R0, 1	;R0 = END - START
	AND R1, R1, 0
	ADD R1, R1, 2	;R1 = 2
	UDIV		;R0 = END - START / 2
	ADD R0, R0, R2	;R0 = MID
	LDR R1, R5, 4   ;R1 stores ARR
	ADD R1, R0, R1	;R1 stores MID_ADDR
	LDR R1, R1, 0	;R1 stores MID_VAL
	NOT R1, R1
	ADD R1, R1, 1	;R1 stores -MID_VAL
	LDR R2, R5, 5   ;R2 stores TARGET
	ADD R1, R2, R1	;R1 stores TARGET-MID_VAL
	BRz LAST
	BRn FIRST
	BRp SECOND
FIRST	LDR R1, R5, 6   ;R1 stores START
	LDR R2, R5, 4   ;R2 stores ARR
	LDR R3, R5, 5   ;R3 stores TARGET
	;R0=MID, R1=START, R2=ARR, R3=TARGET
	ADD R6, R6, -4  ; Add arguments onto stack
    	STR R0, R6, 3	; end at the bottom
	STR R1, R6, 2	; start above end
	STR R3, R6, 1	; TARGET above START
	STR R2, R6, 0	; ARR above TARGET
	JSR BIN_SEARCH
	LDR R0, R6, 0   ; R0 = return value
    	ADD R6, R6, 5   ; Pop off return value and 4 args
	BR LAST
SECOND	LDR R1, R5, 7   ;R1 stores END
	LDR R2, R5, 4   ;R2 stores ARR
	LDR R3, R5, 5   ;R3 stores TARGET
	ADD R0, R0, 1	;R0 stores MID+1
	;R0=MID, R1=END, R2=ARR, R3=TARGET
	ADD R6, R6, -4  ; Add arguments onto stack
    	STR R1, R6, 3	; end at the bottom
	STR R0, R6, 2	; start above end
	STR R3, R6, 1	; TARGET above START
	STR R2, R6, 0	; ARR above TARGET
	JSR BIN_SEARCH
	LDR R0, R6, 0       ; R0 = return value
    	ADD R6, R6, 5       ; Pop off return value and 4 args
	BR LAST
NOTFOUND
	AND R0, R0, 0
	ADD R0, R0, -1
;save result in RV
LAST	STR R0, R5, #3 ;store answer into return value
;restore register
	LDR R0, R5, 0  ;load R0 back
	LDR R1, R5, -1 ;load R1 back
	LDR R2, R5, -2 ;load R2 back
	LDR R3, R5, -3 ;load R3 back
	LDR R4, R5, -4 ;load R4 back
	ADD R6, R6, 5 ;tear down the top
;tear down the rest
	LDR R7, R5, 2  ; Restore return address
	ADD R6, R5, 1  ; Move SP to old FP
   	LDR R5, R5, 1  ; Resore old FP
    	ADD R6, R6, 2  ; Move SP to point at the return value
    	RET

.end
