[FORMAT "WCOFF"]
[INSTRSET "i486p"]
[OPTIMIZE 1]
[OPTION 1]
[BITS 32]
	EXTERN	_init_gdtidt
	EXTERN	_init_pic
	EXTERN	_io_sti
	EXTERN	_fifo32_init
	EXTERN	_init_pit
	EXTERN	_init_keyboard
	EXTERN	_enable_mouse
	EXTERN	_io_out8
	EXTERN	_memtest
	EXTERN	_memman_init
	EXTERN	_memman_free
	EXTERN	_init_palette
	EXTERN	_shtctl_init
	EXTERN	_task_init
	EXTERN	_task_run
	EXTERN	_sheet_alloc
	EXTERN	_memman_alloc_4k
	EXTERN	_sheet_setbuf
	EXTERN	_init_screen8
	EXTERN	_make_window8
	EXTERN	_make_textbox8
	EXTERN	_task_alloc
	EXTERN	_console_task
	EXTERN	_timer_alloc
	EXTERN	_timer_init
	EXTERN	_timer_settime
	EXTERN	_init_mouse_cursor8
	EXTERN	_sheet_slide
	EXTERN	_sheet_updown
	EXTERN	_fifo32_put
	EXTERN	_fifo32_status
	EXTERN	_io_cli
	EXTERN	_fifo32_get
	EXTERN	_boxfill8
	EXTERN	_sheet_refresh
	EXTERN	_mouse_decode
	EXTERN	_keytable0
	EXTERN	_putfonts8_asc_sht
	EXTERN	_wait_KBC_sendready
	EXTERN	_cons_putstr0
	EXTERN	_asm_end_app
	EXTERN	_make_wtitle8
	EXTERN	_keytable1
	EXTERN	_task_sleep
[FILE "bootpack.c"]
[SECTION .data]
_keytable0:
	DB	0
	DB	0
	DB	49
	DB	50
	DB	51
	DB	52
	DB	53
	DB	54
	DB	55
	DB	56
	DB	57
	DB	48
	DB	45
	DB	61
	DB	0
	DB	0
	DB	81
	DB	87
	DB	69
	DB	82
	DB	84
	DB	89
	DB	85
	DB	73
	DB	79
	DB	80
	DB	91
	DB	93
	DB	0
	DB	0
	DB	65
	DB	83
	DB	68
	DB	70
	DB	71
	DB	72
	DB	74
	DB	75
	DB	76
	DB	59
	DB	39
	DB	96
	DB	0
	DB	92
	DB	90
	DB	88
	DB	67
	DB	86
	DB	66
	DB	78
	DB	77
	DB	44
	DB	46
	DB	47
	DB	0
	DB	42
	DB	0
	DB	32
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	55
	DB	56
	DB	57
	DB	45
	DB	52
	DB	53
	DB	54
	DB	43
	DB	49
	DB	50
	DB	51
	DB	48
	DB	46
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
_keytable1:
	DB	0
	DB	0
	DB	33
	DB	64
	DB	35
	DB	36
	DB	37
	DB	94
	DB	38
	DB	42
	DB	40
	DB	41
	DB	95
	DB	43
	DB	0
	DB	0
	DB	81
	DB	87
	DB	69
	DB	82
	DB	84
	DB	89
	DB	85
	DB	73
	DB	79
	DB	80
	DB	123
	DB	125
	DB	0
	DB	0
	DB	65
	DB	83
	DB	68
	DB	70
	DB	71
	DB	72
	DB	74
	DB	75
	DB	76
	DB	58
	DB	34
	DB	126
	DB	0
	DB	124
	DB	90
	DB	88
	DB	67
	DB	86
	DB	66
	DB	78
	DB	77
	DB	60
	DB	62
	DB	63
	DB	0
	DB	42
	DB	0
	DB	32
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	55
	DB	56
	DB	57
	DB	45
	DB	52
	DB	53
	DB	54
	DB	43
	DB	49
	DB	50
	DB	51
	DB	48
	DB	46
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
	DB	0
LC0:
	DB	"console",0x00
LC1:
	DB	"task_a",0x00
LC3:
	DB	0x0A,"Break(key) :",0x0A,0x00
LC2:
	DB	" ",0x00
[SECTION .text]
	GLOBAL	_HariMain
_HariMain:
	PUSH	EBP
	MOV	EBP,ESP
	PUSH	EDI
	PUSH	ESI
	PUSH	EBX
	SUB	ESP,1100
	MOV	DWORD [-1092+EBP],0
	MOV	DWORD [-1096+EBP],0
	MOV	AL,BYTE [4081]
	SAR	AL,4
	MOV	EDX,EAX
	AND	EDX,7
	MOV	DWORD [-1100+EBP],EDX
	MOV	DWORD [-1104+EBP],-1
	MOV	DWORD [-1108+EBP],0
	CALL	_init_gdtidt
	CALL	_init_pic
	CALL	_io_sti
	LEA	EAX,DWORD [-636+EBP]
	PUSH	0
	PUSH	EAX
	LEA	EAX,DWORD [-92+EBP]
	PUSH	128
	PUSH	EAX
	CALL	_fifo32_init
	CALL	_init_pit
	LEA	EDX,DWORD [-92+EBP]
	PUSH	256
	PUSH	EDX
	CALL	_init_keyboard
	LEA	EAX,DWORD [-780+EBP]
	PUSH	EAX
	LEA	EAX,DWORD [-92+EBP]
	PUSH	512
	PUSH	EAX
	CALL	_enable_mouse
	ADD	ESP,36
	PUSH	248
	PUSH	33
	CALL	_io_out8
	PUSH	239
	PUSH	161
	CALL	_io_out8
	LEA	EDX,DWORD [-124+EBP]
	PUSH	0
	LEA	EAX,DWORD [-764+EBP]
	PUSH	EAX
	PUSH	32
	PUSH	EDX
	CALL	_fifo32_init
	ADD	ESP,32
	PUSH	-1073741825
	PUSH	4194304
	CALL	_memtest
	PUSH	3932160
	MOV	DWORD [-1056+EBP],EAX
	CALL	_memman_init
	PUSH	647168
	PUSH	4096
	PUSH	3932160
	CALL	_memman_free
	MOV	EAX,DWORD [-1056+EBP]
	SUB	EAX,4194304
	PUSH	EAX
	PUSH	4194304
	PUSH	3932160
	CALL	_memman_free
	ADD	ESP,36
	CALL	_init_palette
	MOVSX	EAX,WORD [4086]
	PUSH	EAX
	MOVSX	EAX,WORD [4084]
	PUSH	EAX
	PUSH	DWORD [4088]
	PUSH	3932160
	CALL	_shtctl_init
	PUSH	3932160
	MOV	ESI,EAX
	CALL	_task_init
	PUSH	2
	PUSH	1
	MOV	DWORD [-1080+EBP],EAX
	PUSH	EAX
	MOV	DWORD [-68+EBP],EAX
	CALL	_task_run
	ADD	ESP,32
	PUSH	ESI
	CALL	_sheet_alloc
	MOVSX	EDX,WORD [4086]
	MOV	DWORD [-1068+EBP],EAX
	MOVSX	EAX,WORD [4084]
	IMUL	EAX,EDX
	PUSH	EAX
	PUSH	3932160
	CALL	_memman_alloc_4k
	PUSH	-1
	MOV	EBX,EAX
	MOVSX	EAX,WORD [4086]
	PUSH	EAX
	MOVSX	EAX,WORD [4084]
	PUSH	EAX
	PUSH	EBX
	PUSH	DWORD [-1068+EBP]
	CALL	_sheet_setbuf
	ADD	ESP,32
	MOVSX	EAX,WORD [4086]
	PUSH	EAX
	MOVSX	EAX,WORD [4084]
	PUSH	EAX
	PUSH	EBX
	LEA	EBX,DWORD [-1036+EBP]
	CALL	_init_screen8
	PUSH	ESI
	CALL	_sheet_alloc
	PUSH	42240
	PUSH	3932160
	MOV	DWORD [-1076+EBP],EAX
	CALL	_memman_alloc_4k
	PUSH	-1
	PUSH	165
	MOV	DWORD [-1064+EBP],EAX
	PUSH	256
	PUSH	EAX
	PUSH	DWORD [-1076+EBP]
	CALL	_sheet_setbuf
	ADD	ESP,44
	PUSH	0
	PUSH	LC0
	PUSH	165
	PUSH	256
	PUSH	DWORD [-1064+EBP]
	CALL	_make_window8
	PUSH	0
	PUSH	128
	PUSH	240
	PUSH	28
	PUSH	8
	PUSH	DWORD [-1076+EBP]
	CALL	_make_textbox8
	ADD	ESP,44
	CALL	_task_alloc
	PUSH	65536
	PUSH	3932160
	MOV	DWORD [-1084+EBP],EAX
	CALL	_memman_alloc_4k
	MOV	EDX,DWORD [-1084+EBP]
	ADD	EAX,65524
	MOV	DWORD [100+EDX],EAX
	MOV	DWORD [76+EDX],_console_task
	MOV	DWORD [116+EDX],8
	MOV	DWORD [120+EDX],16
	MOV	DWORD [124+EDX],8
	MOV	DWORD [128+EDX],8
	MOV	DWORD [132+EDX],8
	MOV	DWORD [136+EDX],8
	MOV	EDX,DWORD [-1076+EBP]
	MOV	DWORD [4+EAX],EDX
	MOV	EDX,DWORD [-1084+EBP]
	MOV	EAX,DWORD [100+EDX]
	MOV	EDX,DWORD [-1056+EBP]
	MOV	DWORD [8+EAX],EDX
	PUSH	2
	PUSH	2
	PUSH	DWORD [-1084+EBP]
	CALL	_task_run
	MOV	DWORD [4068],ESI
	PUSH	ESI
	CALL	_sheet_alloc
	PUSH	8320
	PUSH	3932160
	MOV	EDI,EAX
	CALL	_memman_alloc_4k
	ADD	ESP,32
	PUSH	-1
	MOV	DWORD [-1060+EBP],EAX
	PUSH	52
	PUSH	144
	PUSH	EAX
	PUSH	EDI
	CALL	_sheet_setbuf
	PUSH	1
	PUSH	LC1
	PUSH	52
	PUSH	144
	PUSH	DWORD [-1060+EBP]
	CALL	_make_window8
	ADD	ESP,40
	PUSH	7
	PUSH	16
	PUSH	128
	PUSH	28
	PUSH	8
	PUSH	EDI
	CALL	_make_textbox8
	MOV	DWORD [-1048+EBP],8
	MOV	DWORD [-1052+EBP],7
	CALL	_timer_alloc
	PUSH	1
	MOV	DWORD [-1088+EBP],EAX
	LEA	EAX,DWORD [-92+EBP]
	PUSH	EAX
	PUSH	DWORD [-1088+EBP]
	CALL	_timer_init
	ADD	ESP,36
	PUSH	50
	PUSH	DWORD [-1088+EBP]
	CALL	_timer_settime
	PUSH	ESI
	CALL	_sheet_alloc
	PUSH	99
	PUSH	16
	PUSH	16
	MOV	DWORD [-1072+EBP],EAX
	PUSH	EBX
	PUSH	EAX
	CALL	_sheet_setbuf
	ADD	ESP,32
	PUSH	99
	PUSH	EBX
	MOV	EBX,2
	CALL	_init_mouse_cursor8
	MOVSX	EAX,WORD [4084]
	LEA	ECX,DWORD [-16+EAX]
	MOV	EAX,ECX
	CDQ
	IDIV	EBX
	MOV	DWORD [-1040+EBP],EAX
	MOVSX	EAX,WORD [4086]
	PUSH	0
	LEA	ECX,DWORD [-44+EAX]
	PUSH	0
	MOV	EAX,ECX
	CDQ
	IDIV	EBX
	PUSH	DWORD [-1068+EBP]
	MOV	DWORD [-1044+EBP],EAX
	CALL	_sheet_slide
	PUSH	4
	PUSH	32
	PUSH	DWORD [-1076+EBP]
	CALL	_sheet_slide
	ADD	ESP,32
	PUSH	56
	PUSH	64
	PUSH	EDI
	CALL	_sheet_slide
	PUSH	DWORD [-1044+EBP]
	PUSH	DWORD [-1040+EBP]
	PUSH	DWORD [-1072+EBP]
	CALL	_sheet_slide
	PUSH	0
	PUSH	DWORD [-1068+EBP]
	CALL	_sheet_updown
	ADD	ESP,32
	PUSH	1
	PUSH	DWORD [-1076+EBP]
	CALL	_sheet_updown
	PUSH	2
	PUSH	EDI
	CALL	_sheet_updown
	PUSH	3
	PUSH	DWORD [-1072+EBP]
	CALL	_sheet_updown
	LEA	EDX,DWORD [-124+EBP]
	PUSH	237
	PUSH	EDX
	CALL	_fifo32_put
	LEA	EAX,DWORD [-124+EBP]
	ADD	ESP,32
	PUSH	DWORD [-1100+EBP]
	PUSH	EAX
	CALL	_fifo32_put
	POP	ECX
	POP	EBX
L2:
	LEA	EBX,DWORD [-124+EBP]
	PUSH	EBX
	CALL	_fifo32_status
	POP	EDX
	TEST	EAX,EAX
	JLE	L5
	CMP	DWORD [-1104+EBP],0
	JS	L60
L5:
	LEA	EBX,DWORD [-92+EBP]
	CALL	_io_cli
	PUSH	EBX
	CALL	_fifo32_status
	POP	ESI
	TEST	EAX,EAX
	JE	L61
	PUSH	EBX
	CALL	_fifo32_get
	MOV	ESI,EAX
	CALL	_io_sti
	POP	ECX
	LEA	EAX,DWORD [-256+ESI]
	CMP	EAX,255
	JBE	L62
	LEA	EAX,DWORD [-512+ESI]
	CMP	EAX,255
	JBE	L63
	CMP	ESI,1
	JG	L2
	TEST	ESI,ESI
	JE	L53
	PUSH	0
	PUSH	EBX
	PUSH	DWORD [-1088+EBP]
	CALL	_timer_init
	ADD	ESP,12
	CMP	DWORD [-1052+EBP],0
	JS	L55
	MOV	DWORD [-1052+EBP],0
L55:
	PUSH	50
	PUSH	DWORD [-1088+EBP]
	CALL	_timer_settime
	POP	EAX
	POP	EDX
	CMP	DWORD [-1052+EBP],0
	JS	L2
	MOV	EAX,DWORD [-1048+EBP]
	PUSH	43
	ADD	EAX,7
	PUSH	EAX
	PUSH	28
	PUSH	DWORD [-1048+EBP]
	MOVZX	EAX,BYTE [-1052+EBP]
	PUSH	EAX
	PUSH	DWORD [4+EDI]
	PUSH	DWORD [EDI]
	CALL	_boxfill8
	MOV	EAX,DWORD [-1048+EBP]
	PUSH	44
	ADD	EAX,8
	PUSH	EAX
	PUSH	28
	PUSH	DWORD [-1048+EBP]
	PUSH	EDI
	CALL	_sheet_refresh
	ADD	ESP,48
	JMP	L2
L53:
	PUSH	1
	PUSH	EBX
	PUSH	DWORD [-1088+EBP]
	CALL	_timer_init
	ADD	ESP,12
	CMP	DWORD [-1052+EBP],0
	JS	L55
	MOV	DWORD [-1052+EBP],7
	JMP	L55
L63:
	MOV	EDX,ESI
	MOVZX	EAX,DL
	PUSH	EAX
	LEA	EAX,DWORD [-780+EBP]
	PUSH	EAX
	CALL	_mouse_decode
	POP	ECX
	POP	EBX
	TEST	EAX,EAX
	JE	L2
	MOV	EAX,DWORD [-772+EBP]
	MOV	EDX,DWORD [-776+EBP]
	ADD	DWORD [-1044+EBP],EAX
	ADD	DWORD [-1040+EBP],EDX
	JS	L64
L46:
	CMP	DWORD [-1044+EBP],0
	JS	L65
L47:
	MOVSX	EAX,WORD [4084]
	DEC	EAX
	CMP	DWORD [-1040+EBP],EAX
	JLE	L48
	MOV	DWORD [-1040+EBP],EAX
L48:
	MOVSX	EAX,WORD [4086]
	DEC	EAX
	CMP	DWORD [-1044+EBP],EAX
	JLE	L49
	MOV	DWORD [-1044+EBP],EAX
L49:
	PUSH	DWORD [-1044+EBP]
	PUSH	DWORD [-1040+EBP]
	PUSH	DWORD [-1072+EBP]
	CALL	_sheet_slide
	ADD	ESP,12
	TEST	DWORD [-768+EBP],1
	JE	L2
	MOV	EAX,DWORD [-1044+EBP]
	SUB	EAX,8
	PUSH	EAX
	MOV	EAX,DWORD [-1040+EBP]
	SUB	EAX,80
	PUSH	EAX
	PUSH	EDI
	CALL	_sheet_slide
	ADD	ESP,12
	JMP	L2
L65:
	MOV	DWORD [-1044+EBP],0
	JMP	L47
L64:
	MOV	DWORD [-1040+EBP],0
	JMP	L46
L62:
	CMP	ESI,383
	JG	L9
	CMP	DWORD [-1096+EBP],0
	JNE	L10
	MOV	AL,BYTE [_keytable0-256+ESI]
L59:
	MOV	BYTE [-60+EBP],AL
L12:
	MOV	DL,BYTE [-60+EBP]
	LEA	EAX,DWORD [-65+EDX]
	CMP	AL,25
	JA	L13
	TEST	DWORD [-1100+EBP],4
	JNE	L58
	CMP	DWORD [-1096+EBP],0
	JE	L15
L13:
	MOV	AL,BYTE [-60+EBP]
	TEST	AL,AL
	JE	L17
	CMP	DWORD [-1092+EBP],0
	JNE	L18
	CMP	DWORD [-1048+EBP],127
	JG	L17
	PUSH	1
	LEA	EAX,DWORD [-60+EBP]
	PUSH	EAX
	PUSH	7
	PUSH	0
	PUSH	28
	PUSH	DWORD [-1048+EBP]
	PUSH	EDI
	MOV	BYTE [-59+EBP],0
	CALL	_putfonts8_asc_sht
	ADD	ESP,28
	ADD	DWORD [-1048+EBP],8
L17:
	CMP	ESI,270
	JE	L66
L21:
	CMP	ESI,284
	JE	L67
L25:
	CMP	ESI,271
	JE	L68
L27:
	CMP	ESI,298
	JE	L69
L30:
	CMP	ESI,310
	JE	L70
L31:
	CMP	ESI,426
	JE	L71
L32:
	CMP	ESI,438
	JE	L72
L33:
	CMP	ESI,314
	JE	L73
L34:
	CMP	ESI,325
	JE	L74
L35:
	CMP	ESI,326
	JE	L75
L36:
	CMP	ESI,285
	JE	L76
L37:
	CMP	ESI,413
	JE	L77
L38:
	CMP	ESI,302
	JE	L78
L39:
	CMP	ESI,506
	JE	L79
L40:
	CMP	ESI,510
	JE	L80
L41:
	CMP	DWORD [-1052+EBP],0
	JS	L42
	MOV	EAX,DWORD [-1048+EBP]
	PUSH	43
	ADD	EAX,7
	PUSH	EAX
	PUSH	28
	PUSH	DWORD [-1048+EBP]
	MOVZX	EAX,BYTE [-1052+EBP]
	PUSH	EAX
	PUSH	DWORD [4+EDI]
	PUSH	DWORD [EDI]
	CALL	_boxfill8
	ADD	ESP,28
L42:
	MOV	EAX,DWORD [-1048+EBP]
	PUSH	44
	ADD	EAX,8
	PUSH	EAX
	PUSH	28
	PUSH	DWORD [-1048+EBP]
	PUSH	EDI
	CALL	_sheet_refresh
	ADD	ESP,20
	JMP	L2
L80:
	CALL	_wait_KBC_sendready
	PUSH	DWORD [-1104+EBP]
	PUSH	96
	CALL	_io_out8
	POP	ESI
	POP	EAX
	JMP	L41
L79:
	MOV	DWORD [-1104+EBP],-1
	JMP	L40
L78:
	CMP	DWORD [-1108+EBP],0
	JE	L39
	MOV	EAX,DWORD [-1084+EBP]
	CMP	DWORD [52+EAX],0
	JE	L39
	PUSH	LC3
	PUSH	DWORD [4076]
	CALL	_cons_putstr0
	CALL	_io_cli
	MOV	EDX,DWORD [-1084+EBP]
	MOV	EAX,DWORD [-1084+EBP]
	ADD	EAX,48
	MOV	DWORD [84+EDX],EAX
	MOV	DWORD [76+EDX],_asm_end_app
	CALL	_io_sti
	POP	EAX
	POP	EDX
	JMP	L39
L77:
	AND	DWORD [-1108+EBP],-2
	JMP	L38
L76:
	OR	DWORD [-1108+EBP],1
	JMP	L37
L75:
	PUSH	237
	LEA	EBX,DWORD [-124+EBP]
	PUSH	EBX
	XOR	DWORD [-1100+EBP],1
	CALL	_fifo32_put
	PUSH	DWORD [-1100+EBP]
	PUSH	EBX
	CALL	_fifo32_put
	ADD	ESP,16
	JMP	L36
L74:
	PUSH	237
	LEA	EBX,DWORD [-124+EBP]
	PUSH	EBX
	XOR	DWORD [-1100+EBP],2
	CALL	_fifo32_put
	PUSH	DWORD [-1100+EBP]
	PUSH	EBX
	CALL	_fifo32_put
	ADD	ESP,16
	JMP	L35
L73:
	PUSH	237
	LEA	EBX,DWORD [-124+EBP]
	PUSH	EBX
	XOR	DWORD [-1100+EBP],4
	CALL	_fifo32_put
	PUSH	DWORD [-1100+EBP]
	PUSH	EBX
	CALL	_fifo32_put
	ADD	ESP,16
	JMP	L34
L72:
	AND	DWORD [-1096+EBP],-3
	JMP	L33
L71:
	AND	DWORD [-1096+EBP],-2
	JMP	L32
L70:
	OR	DWORD [-1096+EBP],2
	JMP	L31
L69:
	OR	DWORD [-1096+EBP],1
	JMP	L30
L68:
	CMP	DWORD [-1092+EBP],0
	JNE	L28
	PUSH	0
	PUSH	LC1
	PUSH	DWORD [4+EDI]
	PUSH	DWORD [-1060+EBP]
	MOV	DWORD [-1092+EBP],1
	CALL	_make_wtitle8
	MOV	EDX,DWORD [-1076+EBP]
	PUSH	1
	PUSH	LC0
	PUSH	DWORD [4+EDX]
	PUSH	DWORD [-1064+EBP]
	CALL	_make_wtitle8
	MOV	EAX,DWORD [-1048+EBP]
	ADD	ESP,32
	ADD	EAX,7
	MOV	DWORD [-1052+EBP],-1
	PUSH	43
	PUSH	EAX
	PUSH	28
	PUSH	DWORD [-1048+EBP]
	PUSH	7
	PUSH	DWORD [4+EDI]
	PUSH	DWORD [EDI]
	CALL	_boxfill8
	MOV	EAX,DWORD [-1084+EBP]
	PUSH	2
	ADD	EAX,16
	PUSH	EAX
	CALL	_fifo32_put
	ADD	ESP,36
L29:
	PUSH	21
	PUSH	DWORD [4+EDI]
	PUSH	0
	PUSH	0
	PUSH	EDI
	CALL	_sheet_refresh
	MOV	EDX,DWORD [-1076+EBP]
	PUSH	21
	PUSH	DWORD [4+EDX]
	PUSH	0
	PUSH	0
	PUSH	EDX
	CALL	_sheet_refresh
	ADD	ESP,40
	JMP	L27
L28:
	PUSH	1
	PUSH	LC1
	PUSH	DWORD [4+EDI]
	PUSH	DWORD [-1060+EBP]
	MOV	DWORD [-1092+EBP],0
	CALL	_make_wtitle8
	MOV	EAX,DWORD [-1076+EBP]
	PUSH	0
	PUSH	LC0
	PUSH	DWORD [4+EAX]
	PUSH	DWORD [-1064+EBP]
	CALL	_make_wtitle8
	MOV	EAX,DWORD [-1084+EBP]
	ADD	ESP,32
	ADD	EAX,16
	MOV	DWORD [-1052+EBP],0
	PUSH	3
	PUSH	EAX
	CALL	_fifo32_put
	POP	ECX
	POP	EBX
	JMP	L29
L67:
	CMP	DWORD [-1092+EBP],0
	JE	L25
	MOV	EAX,DWORD [-1084+EBP]
	PUSH	266
	ADD	EAX,16
	PUSH	EAX
	CALL	_fifo32_put
	POP	EAX
	POP	EDX
	JMP	L25
L66:
	CMP	DWORD [-1092+EBP],0
	JNE	L22
	CMP	DWORD [-1048+EBP],8
	JLE	L21
	PUSH	1
	PUSH	LC2
	PUSH	7
	PUSH	0
	PUSH	28
	PUSH	DWORD [-1048+EBP]
	PUSH	EDI
	CALL	_putfonts8_asc_sht
	ADD	ESP,28
	SUB	DWORD [-1048+EBP],8
	JMP	L21
L22:
	MOV	EAX,DWORD [-1084+EBP]
	PUSH	264
	ADD	EAX,16
	PUSH	EAX
	CALL	_fifo32_put
	POP	ECX
	POP	EBX
	JMP	L21
L18:
	MOVSX	EAX,AL
	ADD	EAX,256
	PUSH	EAX
	MOV	EAX,DWORD [-1084+EBP]
	ADD	EAX,16
	PUSH	EAX
	CALL	_fifo32_put
	POP	EAX
	POP	EDX
	JMP	L17
L15:
	LEA	EAX,DWORD [32+EDX]
	MOV	BYTE [-60+EBP],AL
	JMP	L13
L58:
	CMP	DWORD [-1096+EBP],0
	JE	L13
	JMP	L15
L10:
	MOV	AL,BYTE [_keytable1-256+ESI]
	JMP	L59
L9:
	MOV	BYTE [-60+EBP],0
	JMP	L12
L61:
	PUSH	DWORD [-1080+EBP]
	CALL	_task_sleep
	CALL	_io_sti
	POP	EBX
	JMP	L2
L60:
	PUSH	EBX
	CALL	_fifo32_get
	MOV	DWORD [-1104+EBP],EAX
	CALL	_wait_KBC_sendready
	PUSH	DWORD [-1104+EBP]
	PUSH	96
	CALL	_io_out8
	ADD	ESP,12
	JMP	L5
