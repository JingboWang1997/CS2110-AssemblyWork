;;===============================
;; CS 2110 Fall 2017
;; Homework 7 - Functions & Recursion
;; Name:
;;===============================

; DO NOT REMOVE THIS LINE
;@plugin filename=lc3_udiv vector=x80

.orig x3000
    LD R6, STACK

    ; TODO: Setup GCD call with arguments A and B

    JSR GCD

    ; TODO: Store the return value in ANSWER

    HALT


A       .fill 20
B       .fill 16
ANSWER  .blkw 1
STACK   .fill xF000



GCD
    ; TODO: Implement GCD here

.end
