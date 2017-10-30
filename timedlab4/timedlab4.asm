;;===============================
;; Timed Lab 4 (Fall 2017)
;;
;; Name: YOUR NAME HERE
;;===============================
;; Write a program that recursively determines if an
;; array is a palindrome or not

.orig x3000

;;=====================================
;; Call ISPALI subroutine with correct arguments here
;;=====================================

	LD R6, STACK        ; Initialize stack

	; TODO: Setup ISPALI call with arguments start, end, ARR

	LD R0, ISPALI_ADDR
	JSRR R0 			; call ISPALI

	; TODO: Store the return value in ANSWER

	HALT

ARR 				.fill x4000
LENGTH 				.fill 10
ANSWER      		.blkw 1         ; Store ANSWER here
ISPALI_ADDR			.fill ISPALI
STACK       		.fill xF000
.end

.orig x4000
.fill 1
.fill 2
.fill 3
.fill 4
.fill 5
.fill 5
.fill 4
.fill 3
.fill 2
.fill 1

.end
;;=====================================
;; Implement your ISPALI subroutine here
;;=====================================

.orig x5000
ISPALI


.end
