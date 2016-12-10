.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		zjmp %:live

#ligne 4 colonne 1 et 2 : "l2" est un label il peut etre compose d'une chaine de caracteres parmis LABEL_CHARS (abcdefghijklmnopqrstuvwxyz_0123456789).

#ligne 4 colonne 3 : ":" est un LABEL_CHAR il doit suivre le label.

#ligne 4 colonne 9 a 11 : c'est l'OP code, il doit etre suivie par ses parametres puis un SEPARATOR_CHAR (',')
