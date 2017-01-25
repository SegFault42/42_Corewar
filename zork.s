.name				"Le système hexadécimal est utilisé notamment en électronique numérique et en informatique car il est particulièrement com ;jlkjh
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
