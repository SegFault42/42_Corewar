.name ""
.comment "qwerty

l2:



		sti r9, %:live
		and r1, %0, r1

live:		live %1
		zjmp %:live
