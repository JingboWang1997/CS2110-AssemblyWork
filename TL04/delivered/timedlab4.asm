;;===============================
;; Timed Lab 4 (Fall 2017)
;;
;; Name: Jingbo Wang
;;===============================
;; Write a program that recursively determines if an
;; array is a palindrome or not

.orig x3000

;;=====================================
;; Call ISPALI subroutine with correct arguments here
;;=====================================

	LD R6, STACK         ; Initialize stack
	; TODO: Setup ISPALI call with arguments start, end, ARR
	ADD  R6, R6, -3      ; Add arguments onto stack
	AND R0, R0, 0		;clear R0;
	STR  R0, R6, 0		;store start
	LD   R0, LENGTH		
	ADD R0, R0, -1		;get end
	STR R0, R6, 1		;store end
	LD R0, ARR
	STR R0, R6, 2		;store array address
	
	LD R0, ISPALI_ADDR
	JSRR R0		; call ISPALI

	LDR  R0, R6, 0       	; R0 = return value
   	ST   R0, ANSWER	 	; ANSWER = return value
   	ADD  R6, R6, 4       	; Pop off return value and 2 args

	HALT

ARR 				.fill x4000
LENGTH 				.fill 5
ANSWER      		.blkw 1         ; Store ANSWER here
ISPALI_ADDR			.fill ISPALI
STACK       		.fill xF000
.end

.orig x4000
.fill 1
.fill 2
.fill 3
.fill 4
.fill 1

.end
;;=====================================
;; Implement your ISPALI subroutine here
;;=====================================

.orig x5000
ISPALI
	;stack frame
	ADD R6, R6, -3 ; Allocate space for core stack frame (RV, RA, OldFP)
	STR R7, R6, 1  ; Save the Return Address
	STR R5, R6, 0  ; Save old FP
	ADD R5, R6, -1 ; Set new FP
	;save registers
	ADD R6, R6, -4  ; Make space to save R0-R3
    	STR R0, R5, 0   ; Save R0 as 1st local
    	STR R1, R5, -1  ; Save R1 as 2nd local
	STR R2, R5, -2  ; Save R2 as 3rd local
	STR R3, R5, -3	; Save R3 as 4th local 
	;get args off the stack
	LDR R0, R5, #4 ;R0 stores start
	LDR R1, R5, #5 ;R1 stores end
	LDR R2, R5, #6 ;R2 stores array
	;operation
	
	NOT R3, R1	;R3 has NOTR1
	ADD R3, R3, 1	;R3 has -end
	ADD R3, R0, R3	;R3 has start-end
	BRzp PROVE	;return 1
	ADD R0, R0, R2	;R0 has index of start
	ADD R1, R1, R2	;R1 has index of end
	LDR R2, R0, 0	;R2 has the start element
	LDR R3, R1, 0	;R3 has the end element
	NOT R3, R3	
	ADD R3, R3, 1	;R3 has -end element
	ADD R3, R2, R3	;R3 has start element - end element
	BRnp DISPROVE	;retrun -1

	ADD  R6, R6, -3      ; Add arguments onto stack
	LDR R2, R5, 6	;put arr into R2
	LDR R0, R5, 4	;put start into R0
	ADD R0, R0, 1
	LDR R1, R5, 5	;put end into R1
	ADD R1, R1, -1
	STR R2, R6, 2
	STR R1, R6, 1
	STR R0, R6, 0
	JSR ISPALI 			; call ISPALI
	LDR  R0, R6, 0       	; R0 = return value
   	ADD  R6, R6, 4       	; Pop off return value and 2 args
	BR FINISH
PROVE	AND R0, R0, 0	;clear R0
	ADD R0, R0, 1	;R0 = 1
	BR FINISH
DISPROVE
	AND R0, R0, 0	;clear R0
	ADD R0, R0, -1	;R0 = -1
	BR FINISH
	;save result in RV
FINISH	STR R0, R5, #3 ;store answer into return value
	;restore register
	LDR R0, R5, 0 ;load R0 back
	LDR R1, R5, -1 ;load R1 back
	LDR R2, R5, -2 ;load R2 back
	LDR R3, R5, -3 	;load R3 back
	ADD R6, R6, 4 ;tear down the top
	;tear down the rest
	LDR R7, R5, 2  ; Restore return address
	ADD R6, R5, 1  ; Move SP to old FP
   	LDR R5, R5, 1  ; Resore old FP
    	ADD R6, R6, 2  ; Move SP to point at the return value
    	RET

.end
