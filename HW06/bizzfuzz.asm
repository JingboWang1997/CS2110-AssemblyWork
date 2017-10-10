;;===============================
;; Name: Jingbo Wang
;;===============================
;; Write a program to do the following.
;;
;; Given an array of positive integers (`ARRAY`) of length `LENGTH`,
;; for each integer `n` inside the array:
;;      Print 'Bizz' and a newline if `n` is divisible by 3 and not by 5 
;;          (`n mod 3 == 0` and `n mod 5 != 0`)
;;      Print 'Fuzz' and a newline if `n` is divisible by 5 and not by 3
;;          (`n mod 3 != 0` and `n mod 5 == 0`)
;;      Print 'BizzFuzz' and a newline if `n` is divisible by 3 and 5.
;;          (`n mod 3 == 0` and `n mod 5 == 0`)
;;
;; Reminder that the newline character is '\n'. Only print newlines in the
;; iterations where you print something. (i.e. If `n` is 7, don't print
;; anything, but if `n` is 15, print 'BizzFuzz\n'.) 

.orig x3000
	LD R1, ARRAY ;put the first index of array in R1
	LD R2, LENGTH ;put the length in R2
	BRz FINISH ;if array is empty, don't do anything
START	AND R5, R5, #0 ;R5 is the status
	LDR R3, R1, #0 ;put element in array in R3
	ADD R4, R3, #0 ;make a copy to R4
	BRz BF ;if value is zero, print
REPEAT3	ADD R3, R3, #-3
	BRp REPEAT3 ;keep decrement value by 3
	BRz THREE ;the value is divisible by 3
	BRn REPEAT5 ;not divisible by 3, try 5
THREE   ADD R5, R5, #1 ;R5==1 means it is divisible by 3
REPEAT5 ADD R4, R4, #-5
	BRp REPEAT5 ;keep decrement value by 5
	BRz FIVE ;the value is divisible by 5
	BRn NOTFIVE ;not divisible by 5, go to final check
FIVE	ADD R5, R5, #-1 ;R5==-1 means it is divisible by 5
	BRz BF ;if status is 0, print BIZZFUZZ
ABF	BRn F ;if status if negative, print FUZZ
AF	BRnzp FINISH; finish checking
NOTFIVE ADD R5, R5, #0 ;get status
	BRp B ;if status is positive, print BIZZ
AB	BRnzp FINISH; finish checking
FINISH	ADD R1, R1, #1 ;point to the next element
	ADD R2, R2, #-1 ;keep track of counter
	BRp START ;keep looping if there are still more to check
	HALT
BF  	LEA R0, BIZZFUZZ
	PUTS
	BRnzp ABF
F	LEA R0, FUZZ
	PUTS
	BRnzp AF
B	LEA R0, BIZZ
	PUTS
	BRnzp AB
ARRAY       .fill x6000
LENGTH      .fill 5
BIZZ	    .stringz "Bizz\n"
FUZZ	    .stringz "Fuzz\n"
BIZZFUZZ    .stringz "BizzFuzz\n"

.end

;; Sample `ARRAY` for manual testing. The tester will rewrite this and the
;; `LENGTH`.
.orig x6000
.fill 4
.fill 5
.fill 15
.fill 0
.fill 3
.end
