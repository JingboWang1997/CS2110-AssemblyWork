;;==================================
;; CS 2110 Spring 2017
;; Homework 7 - Functions & Recursion
;; Name:Jingbo Wang
;;===================================

.orig x3000
    LD   R6, STACK       ; Initalize stack pointer (R6)

    ; Call leftshift()
    ADD  R6, R6, -2      ; Add arguments onto stack
    LD   R0, LEFTSHIFT_N ; Push args onto stack
    STR  R0, R6, 1
    LD   R0, LEFTSHIFT_NUMBER
    STR  R0, R6, 0
    LD   R0, LEFTSHIFT_ADDR
    JSRR R0              ; Call leftshift(number, n)
    LDR  R0, R6, 0       ; R0 = return value
    ST   R0, LEFTSHIFT_RESULT ; LEFTSHIFT_RESULT = return value
    ADD  R6, R6, 3       ; Pop off return value and 2 args

    ; Call set/clear/isset/toggle(), depending on the address you pass
    ; to the JSRR below (currently CLEAR_ADDR for clear())
    ADD  R6, R6, -2      ; Allocate stack space for arguments
    LD   R0, ARG_INDEX   ; Push args onto stack
    STR  R0, R6, 1
    LD   R0, ARG_BITS
    STR  R0, R6, 0
    LD   R0, TOGGLE_ADDR ; ← Change this line to call different functions
    JSRR R0              ; Call clear(bits, index)
    LDR  R0, R6, 0       ; R0 = return value
    ST   R0, RESULT      ; RESULT = return value
    ADD  R6, R6, 3       ; Pop off return value and 2 args

    HALT

; Args/result for leftshift()
LEFTSHIFT_NUMBER .fill 10
LEFTSHIFT_N      .fill 3
LEFTSHIFT_RESULT .blkw 1

; Args/result for set/clear/isset/toggle()
ARG_BITS         .fill x0000
ARG_INDEX        .fill 3
RESULT           .blkw 1

; Addresses
LEFTSHIFT_ADDR   .fill LEFTSHIFT
CLEAR_ADDR       .fill CLEAR
SET_ADDR         .fill SET
ISSET_ADDR       .fill ISSET
TOGGLE_ADDR      .fill TOGGLE


; Initial value of stack pointer (R6), so this is the address of the
; bottom of the stack
STACK            .fill xF000
.end

; ======================== LEFTSHIFT ========================
.orig x4000
LEFTSHIFT
	;stack frame
	ADD R6, R6, -3 ; Allocate space for core stack frame (RV, RA, OldFP)
    	STR R7, R6, 1  ; Save the Return Address
    	STR R5, R6, 0  ; Save old FP
    	ADD R5, R6, -1 ; Set new FP
	;save registers
	ADD R6, R6, -2  ; Make space to save R0-R1
    	STR R0, R5, 0   ; Save R0 as 1st local
    	STR R1, R5, -1  ; Save R1 as 2nd local
	;get args off the stack
	LDR R0, R5, #4 ;R0 stores the number
	LDR R1, R5, #5 ;R1 stores the shifting index
	;left shift
	BRz LS_END
LS_LOOP	ADD R0, R0, R0 ;R0 leftshift once
	ADD R1, R1, #-1 ;decrement counter
	BRp LS_LOOP
	;save result in RV
LS_END	STR R0, R5, #3 ;store answer into return value
	;restore register
	LDR R0, R5, 0 ;load R0 back
	LDR R1, R5, -1 ;load R1 back
	ADD R6, R6, 2 ;tear down the top
	;tear down the rest
	LDR R7, R5, 2  ; Restore return address
	ADD R6, R5, 1  ; Move SP to old FP
   	LDR R5, R5, 1  ; Resore old FP
    	ADD R6, R6, 2  ; Move SP to point at the return value
    	RET
	
	


; ======================== CLEAR ========================

CLEAR
        ;stack frame
	ADD R6, R6, -3 ; Allocate space for core stack frame (RV, RA, OldFP)
    	STR R7, R6, 1  ; Save the Return Address
    	STR R5, R6, 0  ; Save old FP
    	ADD R5, R6, -1 ; Set new FP
	;save registers
	ADD R6, R6, -4  ; Make space to save R0-R2
    	STR R0, R5, -1  ; Save R0 as 1st local
    	STR R1, R5, -2  ; Save R1 as 2nd local
	STR R2, R5, -3	; Save R2 as 3rd local
	AND R0, R0, 0
	ADD R0, R0, 1	; set mask
	STR R0, R5, 0	; set mask as local variable
	;get args off the stack
	LDR R0, R5, 4 	;R0 stores the number
	LDR R1, R5, 5 	;R1 stores the clear index
	LDR R2, R5, 0 	;R2 has value 1
	;set up for mask (leftshift)
	ADD R6, R6, -2	; Add arguments onto stack
    	STR R1, R6, 1	   
    	STR R2, R6, 0
    	JSR LEFTSHIFT
	LDR R2, R6, 0	; R2 = return value
    	STR R2, R5, 0 	; Local Variable = mask
    	ADD R6, R6, 3	; Pop off return value and 2 args
	;clear
	NOT R2, R2
	AND R0, R0, R2	;finish clearing, result in R0
	;save result
	STR R0, R5, 3
	;Restore your registers
	LDR R0, R5, -1  ; Restore R0 from 1st local
    	LDR R1, R5, -2  ; Restore R1 from 2nd local
    	LDR R2, R5, -3  ; Restore R2 from 3rd local
	ADD R6, R6, 3   ; Tear down locals
	;Tear down core frame & Return
	LDR R7, R5, 2  ; Restore return address
    	ADD R6, R5, 1  ; Move SP to old FP
    	LDR R5, R5, 1  ; Resore old FP
    	ADD R6, R6, 2  ; Move SP to point at the return value
	RET


; ======================== SET ========================
SET
        ;stack frame
	ADD R6, R6, -3 ; Allocate space for core stack frame (RV, RA, OldFP)
    	STR R7, R6, 1  ; Save the Return Address
    	STR R5, R6, 0  ; Save old FP
    	ADD R5, R6, -1 ; Set new FP
	;save registers
	ADD R6, R6, -4  ; Make space to save R0-R2
    	STR R0, R5, -1  ; Save R0 as 1st local
    	STR R1, R5, -2  ; Save R1 as 2nd local
	STR R2, R5, -3	; Save R2 as 3rd local
	AND R0, R0, 0
	ADD R0, R0, 1	; set mask
	STR R0, R5, 0	; set mask as local variable
	;get args off the stack
	LDR R0, R5, 4 	;R0 stores the number
	LDR R1, R5, 5 	;R1 stores the clear index
	LDR R2, R5, 0 	;R2 has value 1
	;set up for mask (leftshift)
	ADD R6, R6, -2	; Add arguments onto stack
    	STR R1, R6, 1	   
    	STR R2, R6, 0
    	JSR LEFTSHIFT
	LDR R2, R6, 0	; R2 = return value
    	STR R2, R5, 0 	; Local Variable = mask
    	ADD R6, R6, 3	; Pop off return value and 2 args
	;clear
	NOT R2, R2
	NOT R0, R0
	AND R0, R0, R2	
	NOT R0, R0	;finish setting, result in R0
	;save result
	STR R0, R5, 3
	;Restore your registers
	LDR R0, R5, -1  ; Restore R0 from 1st local
    	LDR R1, R5, -2  ; Restore R1 from 2nd local
    	LDR R2, R5, -3  ; Restore R2 from 3rd local
	ADD R6, R6, 3   ; Tear down locals
	;Tear down core frame & Return
	LDR R7, R5, 2  ; Restore return address
    	ADD R6, R5, 1  ; Move SP to old FP
    	LDR R5, R5, 1  ; Resore old FP
    	ADD R6, R6, 2  ; Move SP to point at the return value
	RET


; ======================== ISSET ========================
ISSET
        ;stack frame
	ADD R6, R6, -3 ; Allocate space for core stack frame (RV, RA, OldFP)
    	STR R7, R6, 1  ; Save the Return Address
    	STR R5, R6, 0  ; Save old FP
    	ADD R5, R6, -1 ; Set new FP
	;save registers
	ADD R6, R6, -4  ; Make space to save R0-R2
    	STR R0, R5, -1  ; Save R0 as 1st local
    	STR R1, R5, -2  ; Save R1 as 2nd local
	STR R2, R5, -3	; Save R2 as 3rd local
	AND R0, R0, 0
	ADD R0, R0, 1	; set mask
	STR R0, R5, 0	; set mask as local variable
	;get args off the stack
	LDR R0, R5, 4 	;R0 stores the number
	LDR R1, R5, 5 	;R1 stores the clear index
	LDR R2, R5, 0 	;R2 has value 1
	;set up for mask (leftshift)
	ADD R6, R6, -2	; Add arguments onto stack
    	STR R1, R6, 1	   
    	STR R2, R6, 0
    	JSR LEFTSHIFT
	LDR R2, R6, 0	; R2 = return value
    	STR R2, R5, 0 	; Local Variable = mask
    	ADD R6, R6, 3	; Pop off return value and 2 args
	;clear
	AND R0, R0, R2	
	BRz SKIP
	AND R0, R0, 0
	ADD R0, R0, 1
SKIP	
	;save result
	STR R0, R5, 3
	;Restore your registers
	LDR R0, R5, -1  ; Restore R0 from 1st local
    	LDR R1, R5, -2  ; Restore R1 from 2nd local
    	LDR R2, R5, -3  ; Restore R2 from 3rd local
	ADD R6, R6, 3   ; Tear down locals
	;Tear down core frame & Return
	LDR R7, R5, 2  ; Restore return address
    	ADD R6, R5, 1  ; Move SP to old FP
    	LDR R5, R5, 1  ; Resore old FP
    	ADD R6, R6, 2  ; Move SP to point at the return value
	RET


; ======================== TOGGLE ========================
TOGGLE
        ;stack frame
	ADD R6, R6, -3 ; Allocate space for core stack frame (RV, RA, OldFP)
    	STR R7, R6, 1  ; Save the Return Address
    	STR R5, R6, 0  ; Save old FP
    	ADD R5, R6, -1 ; Set new FP
	;save registers
	ADD R6, R6, -3  ; Make space to save R0-R1
    	STR R0, R5, 0   ; Save R0 as 1st local
    	STR R1, R5, -1  ; Save R1 as 2nd local
	STR R2, R5, -2	; Save R2 as 3rd local
	;get args off the stack
	LDR R0, R5, #5 	;R0 stores the number
	LDR R1, R5, #4 	;R1 stores the shifting index
	;check isset
	ADD R6, R6, -2 	; Add arguments onto stack
    	STR R0, R6, 1	; put in number
    	STR R1, R6, 0	; put in index
    	JSR ISSET
	LDR R2, R6, 0  ; R0 = return value
    	ADD R6, R6, 3  ; Pop off return value and 2 args
	ADD R2, R2, 0	;get R2 in cc
	BRz CALLSET
	BR CALLCLEAR
CALLSET	ADD  R6, R6, -2      ; Allocate stack space for arguments
	STR  R0, R6, 1
	STR  R1, R6, 0
	JSR SET
	LDR  R0, R6, 0       ; R0 = return value
	ADD  R6, R6, 3       ; Pop off return value and 2 args
	BR FINISH
CALLCLEAR
	ADD  R6, R6, -2      ; Allocate stack space for arguments
	STR  R0, R6, 1
	STR  R1, R6, 0
	JSR CLEAR
	LDR  R0, R6, 0       ; R0 = return value
	ADD  R6, R6, 3       ; Pop off return value and 2 args
	;save result in RV
FINISH	STR R0, R5, #3 ;store answer into return value
	;restore register
	LDR R0, R5, 0 ;load R0 back
	LDR R1, R5, -1 ;load R1 back
	ADD R6, R6, 2 ;tear down the top
	;tear down the rest
	LDR R7, R5, 2  ; Restore return address
	ADD R6, R5, 1  ; Move SP to old FP
   	LDR R5, R5, 1  ; Resore old FP
    	ADD R6, R6, 2  ; Move SP to point at the return value
    	RET

.end
