;;==================================
;; CS 2110 Spring 2017
;; Homework 7 - Functions & Recursion
;; Name:
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
    LD   R0, CLEAR_ADDR  ; ← Change this line to call different functions
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
        ; TODO: Implement leftshift() here


; ======================== CLEAR ========================

CLEAR
        ; TODO: Implement clear() here


; ======================== SET ========================
SET
        ; TODO: Implement set() here


; ======================== ISSET ========================
ISSET
        ; TODO: Implement isset() here


; ======================== TOGGLE ========================
TOGGLE
        ; TODO: Implement toggle() here

.end
