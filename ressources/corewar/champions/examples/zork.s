.name "/* :Prog_name Le systeme hexadecimal est utilise notamment en electronique numerique et en informatique car il est particuliie */"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live
