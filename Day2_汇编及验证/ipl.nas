; hello-os
; TAB=4
; DB 一字节指令 DW 两字节  DD 四字节
		ORG		0x7c00			; 指明启动程序装载地址，规定

; 标准FAT12格式软盘专用的代码 Stand FAT12 format floppy code

		JMP		entry
		DB		0x90
		DB		"HELLOIPL"		; 启动扇区名称可以是任意的字符串（8字节）
		DW		512				; 每个扇区（sector）大小（必须512字节）
		DB		1				; 簇（cluster）大小（必须为1个扇区）
		DW		1				; FAT起始位置（一般为第一个扇区）
		DB		2				; FAT个数（必须为2）
		DW		224				; 根目录大小（一般为224项）
		DW		2880			; 该磁盘大小（必须为2880扇区1440*1024/512）
		DB		0xf0			; 磁盘类型（必须为0xf0）
		DW		9				; FAT的长度（必须是9扇区）
		DW		18				; 一个磁道（track）有几个扇区（必须为18）
		DW		2				; 磁头数（必须是2）
		DD		0				; 不使用分区，必须是0
		DD		2880			; 重写一次磁盘大小
		DB		0,0,0x29		; 意义不明（固定）
		DD		0xffffffff		; （可能是）卷标号码
		DB		"HELLO-OS   "	; 磁盘的名称（必须为11字节，不足填空格）
		DB		"FAT12   "		; 磁盘格式名称（必须为8字节，不足填空格）
		RESB	18				; 先空出18字节

; 程序主体

entry:
		MOV		AX,0			; 初始化寄存器
		MOV		SS,AX
		MOV		SP,0x7c00
		MOV		DS,AX
		MOV		ES,AX
; 先将寄存器初始完后，将需要输出的开始地址给SI，输出一字节移动一字节,输出的最后一行为0，当比较为0时就跳出去完成输出
		MOV		SI,msg
putloop:
		MOV		AL,[SI]
		ADD		SI,1			; 给SI加1
		CMP		AL,0
		JE		fin
		MOV		AH,0x0e			; 显示一个文字
		MOV		BX,15			; 指定字符颜色
		INT		0x10			; 调用显卡BIOS
		JMP		putloop
fin:
		HLT						; 让CPU停止，等待指令,而不是无意义空转
		JMP		fin				; 无限循环

msg:
		DB		0x0a, 0x0a		; 换行两次
		DB		"Jie,Kang,Xiao" ;BD 可直接写字符串，汇编会自动查找每个字符对应编码
		DB		0x0a			; 换行
		DB		0

		RESB	0x7dfe-$		; 填写0x00直到0x001fe $是一个变量，表示开始地址因为ORG
							; RESB填多少字节0,用16进制打开是0x1fe，但实际开始位置为0x7c00所以要加上及0x7dfe
		DB		0x55, 0xaa
