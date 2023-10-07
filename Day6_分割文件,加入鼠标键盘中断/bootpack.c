#include "bootpack.h"
#include <stdio.h>

int HariMain(void) // 就是main函数
{
	struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO; // ADR_BOOTINFO宏定义0x00000ff0，在.h中
	char s[40], mcursor[256];
	int mx, my;

	init_gdtidt();
	init_pic();
	io_sti(); /* IDT/PIC的初始化已经完成，于是开放CPU的中断 */

	init_palette();
	init_screen(binfo->vram, binfo->scrnx, binfo->scrny);

	/* 显示鼠标 */
	mx = (binfo->scrnx - 16) / 2; // 计算画面的中心坐标
	my = (binfo->scrny - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);

	sprintf(s, "scrnx = %d", binfo->scrnx);
	putfonts8_asc(binfo->vram, binfo->scrnx, 16, 64, COL8_FFFFFF, s);

	io_out8(PIC0_IMR, 0xf9); /* 开放PIC1和键盘中断(11111001) */
	io_out8(PIC1_IMR, 0xef); /* 开放鼠标中断(11101111) */

	while (1)
	{
		io_hlt();
	}
}
