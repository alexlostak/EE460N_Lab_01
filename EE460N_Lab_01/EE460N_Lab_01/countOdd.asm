.ORIG x3000;
AND R2, R2, #0; keep track of total odd numbers\
LEA R1, TOTAL; keep track of remaining numbers\
LDB R1, R1, #0;\
LEA R3, START;\
LEA R5, COUNTDEST;\

COUNT LDB R4, R3, #0; Current value in R4\
ADD R3, R3, #1; Increment Current address\
AND R4, R4, #1; Determine if odd\
BRnz SKIP; If odd fall through\
ADD R2, R2, #1; Increment total number of odd\
SKIP ADD R1, R1, #-1; Decrement total number of remaining numbers to read\
BRp COUNT;\
STW R2, R5, #0;\
TRAP x23;\
TOTAL .FILL #256;\
START .FILL x4000;\
COUNTDEST .FILL x4100;\
.END