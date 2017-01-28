.name "je suis un programme"

.comment "I'M ALIIIIVE"

live %-1
ld 1892, r1
or r1, %0, r1
ld %184549376, r1
or r1, %0, r1
sti r1, %:test, %0
test: st r1, r2
or r2, %0, r2
st r1, 1510 ;tocheck (P1 | st: r1(184549376) -> 486 | P    1 | st r1 1510)
add r1, r2, r3
or r3, %0, r3
sub r2, r3, r4
or r4, %0, r4
and r5, 4515, r5
or r5, %0, r5
and r5, %15, r5
or r5, %0, r5
and r5, r5, r5
or r5, %0, r5
and 4525, 1215, r5
or r5, %0, r5
and 1355, %15, r5
or r5, %0, r5
and 1565, r5, r5
or r5, %0, r5
and %5, 1715, r5
or r5, %0, r5
and %5, %15, r5
or r5, %0, r5
and %5, r5, r5
or r5, %0, r5
or %5, %5, r6
xor %0, %0, r7
zjmp %3
ldi 1510, %2, r8
or r8, %0, r8
sti r8, %128, %5
or r5, %0, r5
live %-1
fork %0
lld %10, r1
or r1, %0, r1
lldi %128, %2, r8
or r8, %0, r8
live %-1
lfork %0
aff r3
