;;===============================
;; Name: Jingbo Wang
;;===============================
;; Write a program to add an element at a certain index in an array.
;; For the tester, it checks (element, index, [array]) 
;; Note 1) Do not delete any elements from the array, just shift elements when adding
;;      2) Elements can be inserted at the front, middle, or back of the array
;;      3) The array begins at index 0

.orig x3000
	LD R0, INDEX ;put the index in R0
	LD R1, ARRAY ;put the array head in R1
	ADD R0, R0, R1 ;the insert index in R0
	LD R2, LENGTH ;put length in R2
	ADD R1, R1, R2
	ADD R1, R1, #-1 ;put the last index of array in R1 (the source of the first shifting)
	LD R3, INDEX ;put INDEX in R3, cc = p
	BRz SHIFT ;if index == 0; start shifting
SETUP	ADD R2, R2, #-1 ;setup the counter for shifting
	ADD R3, R3, #-1 ;
	BRp SETUP ;R2 now stores the number of elements I need to shift
SHIFT	ADD R3, R1, #1 ;the destination of shifting
	LDR R4, R1, #0 ;put the shifting element in R4
	STR R4, R3, #0 ;put the shifting elemtn back to memory shifted
	ADD R1, R1, #-1
	ADD R3, R3, #-1
	ADD R2, R2, #-1 ;get to the next element
	BRp SHIFT ;shift till the insert index is open
	LD R1, NUMBER ;R1 holds the value to be insert
	STR R1, R0, #0 ;store
    HALT
ARRAY   .fill x6000
LENGTH  .fill 10
NUMBER  .fill 15
INDEX   .fill 3
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
