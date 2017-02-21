.name		"Anything"
.comment	"Where is my free ???"

prepare:
	sti		r1, %:prepwall, %1
	sti		r1, %:prepinvade, %1
	sti		r1, %:wall, %1
	sti		r1, %:wall_fork, %1
	sti		r1, %:alive, %1
	sti		r1, %:alive, %6
	sti		r1, %:alive, %11
	sti		r1, %:alive, %16
	sti		r1, %:alive, %21
	sti		r1, %:alive, %26
	sti		r1, %:alive, %31
	sti		r1, %:alive, %36
	sti		r1, %:alive, %41
	sti		r1, %:alive, %46
	sti		r1, %:alive, %51
	sti		r1, %:alive, %56
	sti		r1, %:alive, %61
	sti		r1, %:alive, %66
	sti		r1, %:alive, %71
	sti		r1, %:alive, %76
	sti		r1, %:alive_fork, %1
	sti		r1, %:invade, %1
	fork	%:alive_fork
	live	%1845735231
	fork	%:prepinvade

prepwall:
	live	%1845735231
	ld		%0, r2
	zjmp	%:wall_fork

wall:
	live	%1845735231
	st		r7, -24
	st		r7, -33
	st		r7, -42
	st		r7, -51
	st		r7, -60
	st		r7, -69
	st		r7, -78
	st		r7, -87
	st		r7, -96
	st		r7, -105
	st		r7, -114
	st		r7, -123
	st		r7, -132
	st		r7, -141
	st		r7, -150
	st		r7, -159
	st		r7, -168
	st		r7, -177
	st		r7, -186
	st		r7, -195
	st		r7, -204
	st		r7, -213
	st		r7, -222
	st		r7, -231
	st		r7, -240
	st		r7, -249
	st		r7, -258
	st		r7, -267
	st		r7, -276
	st		r7, -285
	st		r7, -294
	st		r7, -303
	st		r7, -312
	st		r7, -321
	st		r7, -330
	st		r7, -339
	st		r7, -348
	st		r7, -357
	st		r7, -366
	st		r7, -375
	st		r7, -384
	st		r7, -393
	st		r7, -402
	st		r7, -411
	st		r7, -420
	st		r7, -429
	st		r7, -438
	st		r7, -447
	st		r7, -456
	st		r7, -465
	st		r7, -474
	st		r7, -483
	st		r7, -492
	st		r7, -501
	st		r7, -510
	ld		%0, r2
	zjmp	%:wall

wall_fork:
	live	%1845735231
	fork	%:wall
	zjmp	%:wall_fork

prepinvade:
	live	%1845735231
	st		r1, r2
	st		r1, r3
	st		r1, r4
	st		r1, r5
	st		r1, r6
	st		r1, r7
	st		r1, r8
	st		r1, r9
	st		r1, r10
	st		r1, r11
	st		r1, r12
	st		r1, r13
	st		r1, r14
	st		r1, r15
	st		r1, r16
	ld		%0, r2
	zjmp	%:invade

alive:
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	live	%1845735231
	zjmp	%:alive

alive_fork:
	live	%1845735231
	fork	%:alive
	zjmp	%:alive_fork

invade:
	live	%1845735231
	fork	%:invade
	live	%1845735231
	lfork	%1200
	zjmp	%:invade
