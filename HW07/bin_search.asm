;;===============================
;; CS 2110 Fall 2017
;; Homework 7 - Functions & Recursion
;; Name:
;;===============================

; DO NOT REMOVE THIS LINE
;@plugin filename=lc3_udiv vector=x80

.orig x3000

;;=====================================
;; Call bin_search subroutine with correct arguments here
;;=====================================

	LD R6, STACK        ; Initialize stack

	; TODO: Setup BINSEARCH call with argumuents arr, target, start, end

	LD R0, BIN_SEARCH_ADDR
	JSRR R0 			; call BIN_SEARCH

	; TODO: Store the return value in ANSWER

	HALT

ARR 				.fill x4000
ARR_SIZE 			.fill 16
TARGET 				.fill 7
ANSWER      		.blkw 1         ; Store ANSWER here
BIN_SEARCH_ADDR		.fill BIN_SEARCH
STACK       		.fill xF000


.end
;;=====================================
;; The array to be searched
;;=====================================

.orig x4000
.fill -7
.fill -5
.fill -2
.fill 2
.fill 7
.fill 10
.fill 12
.fill 13
.fill 14
.fill 16
.fill 20
.fill 25
.fill 26
.fill 40
.fill 50
.fill 90

.end
;;=====================================
;; Implement your bin_search subroutine here
;;=====================================

.orig x5000
BIN_SEARCH


.end
