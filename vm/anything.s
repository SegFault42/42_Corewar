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
	ld		%0, r2
	fork	%:alive_fork

prepwall:
	live	%1845735231
	fork	%:wall_fork

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
	zjmp	%:invade

wall:
	live	%1845735231
	st		r2, -24
	st		r2, -33
	st		r2, -42
	st		r2, -51
	st		r2, -60
	st		r2, -69
	st		r2, -78
	st		r2, -87
	st		r2, -96
	st		r2, -105
	st		r2, -114
	st		r2, -123
	st		r2, -132
	st		r2, -141
	st		r2, -150
	st		r2, -159
	st		r2, -168
	st		r2, -177
	st		r2, -186
	st		r2, -195
	st		r2, -204
	st		r2, -213
	st		r2, -222
	st		r2, -231
	st		r2, -240
	st		r2, -249
	st		r2, -258
	st		r2, -267
	st		r2, -276
	st		r2, -285
	st		r2, -294
	st		r2, -303
	st		r2, -312
	st		r2, -321
	st		r2, -330
	st		r2, -339
	st		r2, -348
	st		r2, -357
	st		r2, -366
	st		r2, -375
	st		r2, -384
	st		r2, -393
	st		r2, -402
	st		r2, -411
	st		r2, -420
	st		r2, -429
	st		r2, -438
	st		r2, -447
	st		r2, -456
	st		r2, -465
	st		r2, -474
	st		r2, -483
	st		r2, -492
	st		r2, -501
	st		r2, -510
	zjmp	%:wall

wall_fork:
	live	%1845735231
	fork	%:wall
	zjmp	%:wall_fork

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
	zjmp	%511
