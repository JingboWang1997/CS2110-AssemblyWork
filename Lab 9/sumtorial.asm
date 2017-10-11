;;======================================================================
;; Assignment: Lab 09
;; Description: An assembly program to calculate sumtorial
;;======================================================================

;;Pseudocode:
;;-----------

; Sumtorial(n)
; {
;     int i;
;     int sum = 0;
;     for(i = 0; i < n; i++)
;     {
;        sum += n
;        n = n-1;
;     }
;     return sum;
; }
;;-----------

.orig x3000
	AND R0, R0, 0 	;clear R0
	LD R1, NUM 	;put num in R1
	BRz PRINT 	;if R1 is zero, print zero
LOOP	ADD R0, R0, R1 	;add the current num
	ADD R1, R1, #-1 ;decrement counter
	BRp LOOP	;if the num hasn't reached 0, keep looping
PRINT	ST R0, NUM
	HALT

NUM     .FILL     #5
.end
