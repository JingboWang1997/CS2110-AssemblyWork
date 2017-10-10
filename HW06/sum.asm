;;===============================
;; Name: Jingbo Wang
;;===============================
;; Write a program sums the elements in an array
;; Note 1) Store the sum in the label SUM once the program has terminated. 
;;		2) If SUM is not initially  zero, increment SUM by the sum of the array.
;;      3) The array's length is stored in the label LENGTH
;;      4) The address of the array's first element is stored in the label ARRAY

.orig x3000
	AND R0, R0, #0 ;clear R0
	LD R2, ARRAY ;put the cursor on the first element of array
	LD R4, SUM ;put the current SUM value in R4
	LD R1, LENGTH ;counter for the process
	BRz #4 ;if there is no element in array, skip
ADDING 	LDR R3, R2, #0 ;put the current element of array in R3
	ADD R0, R0, R3 ;add the current element in array to R0
	ADD R2, R2, #1; move the cursor to the next element in the array
	ADD R1, R1, #-1; decrement the counter
	BRp #-5 ;keep looping until counter goes to zero
	ADD R0, R0, R4 ;add the final sum to the initial value of SUM
STORE	ST R0, SUM ;put the final sum to SUM
    HALT
ARRAY   .fill x6000
LENGTH  .fill 10
SUM     .fill 0
.end

.orig x6000
.fill 2
.fill 9
.fill 6
.fill 7
.fill 8
.fill 4
.fill 10
.fill 11
.fill 3
.fill 14
.end
