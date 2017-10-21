.orig x3000

; SETS UP AND CALLS GET_MAX
; YOU DON'T HAVE TO CHANGE THIS

    LD R6, STACK
    
    JSR GET_MAX
    LDR R0, R6, 0
    ST R0, ANSWER
    ADD R6, R6, 1
    HALT

ANSWER .fill 0
STACK  .fill xF000


; Get 2 integers from the user and return the max of the two integers.
; ======================
; FILL OUT THIS FUNCTION
; ======================
GET_MAX
    ; =======================
    ; Build the stack frame
    ; =======================
    ADD R6, R6, -3 ; Allocate space for core stack frame (RV, RA, OldFP)
    STR R7, R6, 1  ; Save the Return Address
    STR R5, R6, 0  ; Save old FP
    ADD R5, R6, -1 ; Set new FP

    ; =======================================
    ; Save the registers you are going to use
    ; =======================================
    ADD R6, R6, -3  ; Make space to save R0-R2
    STR R0, R5, 0   ; Save R0 as 1st local
    STR R1, R5, -1  ; Save R1 as 2nd local
    STR R2, R5, -2  ; Save R2 as 3rd local
    ; ======================================
    ; Get Arguments off the stack
    ; ======================================
    ; No args so do nothing

    ; ============================
    ; LOGIC
    ; ============================
    	AND R1, R1, 0    ; integer = 0
	JSR GET_INT
	JSR GET_INT
	JSR MAX
    ; ======================
    ; Save the result in RV
    ; ======================
    STR R1, R5, 3
    ; ======================
    ; Restore your registers
    ; ======================
    LDR R0, R5, 0   ; Restore R0 from 1st local
    LDR R1, R5, -1  ; Restore R1 from 2nd local
    LDR R2, R5, -2  ; Restore R2 from 3rd local
    ADD R6, R6, 3   ; Tear down locals
    ; ==================================
    ; Tear down the stack frame & Return
    ; ==================================
    LDR R7, R5, 2  ; Restore return address
    ADD R6, R5, 1  ; Move SP to old FP
    LDR R5, R5, 1  ; Resore old FP
    ADD R6, R6, 2  ; Move SP to point at the return value
    RET


; Calculates the max of A and B
; ======================
; FILL OUT THIS FUNCTION
; ======================
MAX
    ; =======================
    ; Build the stack frame
    ; =======================
	ADD R6, R6, -3 ; Allocate space for core stack frame (RV, RA, OldFP)
	STR R7, R6, 1  ; Save the Return Address
	STR R5, R6, 0  ; Save old FP
	ADD R5, R6, -1 ; Set new FP

    ; =======================================
    ; Save the registers you are going to use
    ; =======================================
	ADD R6, R6, -3  ; Make space to save R0-R2
	STR R0, R5, 0   ; Save R0 as 1st local
	STR R1, R5, -1  ; Save R1 as 2nd local
	STR R2, R5, -2  ; Save R2 as 3rd local

    ; ======================================
    ; Get Arguments off the stack
    ; ======================================
	LDR R0, R5, 4 ; Put A into R0
	LDR R1, R5, 5 ; Put B into R1 
    ; ============================
    ; Calculate the max
    ; ============================
    	NOT R2, R1
	ADD R2, R2, #1 ; R2 has -B
	ADD R2, R1, R2 ; R2 has A-B
	BRp RETA
    ; ======================
    ; Save the result in RV
    ; ======================
	STR R1, R5, 3
        
    ; ======================
    ; Restore your registers
    ; ======================
	LDR R0, R5, 0   ; Restore R0 from 1st local
    	LDR R1, R5, -1  ; Restore R1 from 2nd local
    	LDR R2, R5, -2  ; Restore R2 from 3rd local
    	ADD R6, R6, 3   ; Tear down locals
    ; ==================================
    ; Tear down the stack frame & Return
    ; ==================================
	LDR R7, R5, 2  ; Restore return address
	ADD R6, R5, 1  ; Move SP to old FP
        LDR R5, R5, 1  ; Resore old FP
        ADD R6, R6, 2  ; Move SP to point at the return value	
	RET
	RETA	ADD R1, R0, #0


; WE HAVE DONE THIS FOR YOU, DON'T CHANGE THIS
; Gets an integer from the user
; Arguments: None
; Returns: The integer input by the user
; Limitations: cannot handle numbers >= 2^15 (32768)
; (Example: "1234" --> 1234)
; To finish entering your number simply enter a non decimal character
; (Example "123f" --> 123)
GET_INT
    ; =======================
    ; Build the stack frame
    ; =======================
    ADD R6, R6, -3 ; Allocate space for core stack frame (RV, RA, OldFP)
    STR R7, R6, 1  ; Save the Return Address
    STR R5, R6, 0  ; Save old FP
    ADD R5, R6, -1 ; Set new FP

    ; =======================================
    ; Save the registers you are going to use
    ; =======================================
    ADD R6, R6, -3  ; Make space to save R0-R2
    STR R0, R5, 0   ; Save R0 as 1st local
    STR R1, R5, -1  ; Save R1 as 2nd local
    STR R2, R5, -2  ; Save R2 as 3rd local

    ; ======================================
    ; Get Arguments off the stack
    ; ======================================
    ; No args do don't do anything

    ; ============================
    ; Get input from the user
    ; ============================
    AND R1, R1, 0    ; integer = 0
GETC_LOOP
    GETC
    OUT
    
    ; Validate the input
    ; If input < '0'
    LD R2, ASCII_ZERO
    NOT R2, R2
    ADD R2, R2, 1
    ADD R2, R2, R0
    BRn NON_DECIMAL_INPUT
    ; If input > '9'
    LD R2, ASCII_NINE
    NOT R2, R2
    ADD R2, R2, 1
    ADD R2, R2, R0
    BRp NON_DECIMAL_INPUT

    ; Convert the character from ASCII to [0,9]
    LD R2, ASCII_ZERO
    NOT R2, R2
    ADD R2, R2, 1
    ADD R0, R0, R2

    ; Multiplly total * 10
    ADD R6, R6, -2 
    STR R1, R6, 1
    AND R1, R1, 0
    ADD R1, R1, 10
    STR R1, R6, 0
    JSR MULT
    LDR R1, R6, 0
    ADD R6, R6, 3

    ; Add on the new digit
    ADD R1, R1, R0
    BR GETC_LOOP
NON_DECIMAL_INPUT
    
    ; ======================
    ; Save the result in RV
    ; ======================
    STR R1, R5, 3
        
    ; ======================
    ; Restore your registers
    ; ======================
    LDR R0, R5, 0   ; Restore R0 from 1st local
    LDR R1, R5, -1  ; Restore R1 from 2nd local
    LDR R2, R5, -2  ; Restore R2 from 3rd local
    ADD R6, R6, 3   ; Tear down locals
    
    ; =============================
    ; Tear down core frame & Return
    ; =============================
    LDR R7, R5, 2  ; Restore return address
    ADD R6, R5, 1  ; Move SP to old FP
    LDR R5, R5, 1  ; Resore old FP
    ADD R6, R6, 2  ; Move SP to point at the return value
    RET

ASCII_ZERO .fill '0'
ASCII_NINE .fill '9'
comma	   .fill ','

; WE HAVE DONE THIS FOR YOU, DON't CHANGE THIS
; Multiplies A * B
; Args: A, B
; Returns A * B
; Limitations: ONLY MULTIPLIES POSITIVE NUMBERS
MULT
    ; =======================
    ; Build the stack frame
    ; =======================
    ADD R6, R6, -3 ; Allocate space for core stack frame (RV, RA, OldFP)
    STR R7, R6, 1  ; Save the Return Address
    STR R5, R6, 0  ; Save old FP
    ADD R5, R6, -1 ; Set new FP

    ; =======================================
    ; Save the registers you are going to use
    ; =======================================
    ADD R6, R6, -3  ; Make space to save R0-R2
    STR R0, R5, 0   ; Save R0 as 1st local
    STR R1, R5, -1  ; Save R1 as 2nd local
    STR R2, R5, -2  ; Save R2 as 3rd local

    ; ======================================
    ; Get Arguments off the stack
    ; ======================================
    LDR R0, R5, 4 ; Put A into R0
    LDR R1, R5, 5 ; Put B into R1

    ; ============================
    ; Multiply by adding
    ; ============================
    AND R2, R2, 0   ; Total = 0
MULT_LOOP
    ADD R0, R0, 0   ;\
    BRz MULT_DONE   ;/ If A == 0 --> Done
    ADD R2, R2, R1  ; Total = Total + B
    ADD R0, R0, #-1 ; A = A - 1
    BR MULT_LOOP
MULT_DONE
    
    ; ======================
    ; Save the result in RV
    ; ======================
    STR R2, R5, 3
        
    ; ======================
    ; Restore your registers
    ; ======================
    LDR R0, R5, 0   ; Restore R0 from 1st local
    LDR R1, R5, -1  ; Restore R1 from 2nd local
    LDR R2, R5, -2  ; Restore R2 from 3rd local
    ADD R6, R6, 3   ; Tear down locals
    
    ; =============================
    ; Tear down core frame & Return
    ; =============================
    LDR R7, R5, 2  ; Restore return address
    ADD R6, R5, 1  ; Move SP to old FP
    LDR R5, R5, 1  ; Resore old FP
    ADD R6, R6, 2  ; Move SP to point at the return value
    RET

.end
