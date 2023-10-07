/* 告诉C编译器，有函数在别的文件里 */
void io_hlt(void);				  // 停机
void io_cli(void);				  // 禁止中断
void io_out8(int port, int data); // 将值输出到端口
int io_load_eflags(void);		  // 读取中断许可标志的值
void io_store_eflags(int eflags); // 复原中断许可标志
// 用汇编封装的结束

void init_palette(void);																		// 初始化调色板
void set_palette(int start, int end, unsigned char *rgb);										// 设置调色板
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1); // 画框

#define COL8_000000 0
#define COL8_FF0000 1
#define COL8_00FF00 2
#define COL8_FFFF00 3
#define COL8_0000FF 4
#define COL8_FF00FF 5
#define COL8_00FFFF 6
#define COL8_FFFFFF 7
#define COL8_C6C6C6 8
#define COL8_840000 9
#define COL8_008400 10
#define COL8_848400 11
#define COL8_000084 12
#define COL8_840084 13
#define COL8_008484 14
#define COL8_848484 15

/* C语言中的static char语句只能用于数据，相当于汇编中的DB指令 */
static unsigned char table_rgb[16 * 3] = {
	0x00, 0x00, 0x00, /*  0:黑 */
	0xff, 0x00, 0x00, /*  1:梁红 */
	0x00, 0xff, 0x00, /*  2:亮绿 */
	0xff, 0xff, 0x00, /*  3:亮黄 */
	0x00, 0x00, 0xff, /*  4:亮蓝 */
	0xff, 0x00, 0xff, /*  5:亮紫 */
	0x00, 0xff, 0xff, /*  6:浅亮蓝 */
	0xff, 0xff, 0xff, /*  7:白 */
	0xc6, 0xc6, 0xc6, /*  8:亮灰 */
	0x84, 0x00, 0x00, /*  9:暗红 */
	0x00, 0x84, 0x00, /* 10:暗绿 */
	0x84, 0x84, 0x00, /* 11:暗黄 */
	0x00, 0x00, 0x84, /* 12:暗青 */
	0x84, 0x00, 0x84, /* 13:暗紫 */
	0x00, 0x84, 0x84, /* 14:浅暗蓝 */
	0x84, 0x84, 0x84  /* 15:暗灰 */
};

int HariMain(void) // 就是main函数
{
	char *vram; /* 声明变量vram、用于BYTE [...]地址 */
	int xsize, ysize;

	init_palette();			/* 设定调色板 */
	vram = (char *)0xa0000; /* 地址变量赋值 */
	xsize = 320;
	ysize = 200;

	/* 根据 0xa0000 + x + y * 320 计算坐标 8*/
	boxfill8(vram, xsize, COL8_008484, 0, 0, xsize - 1, ysize - 29);
	boxfill8(vram, xsize, COL8_C6C6C6, 0, ysize - 28, xsize - 1, ysize - 28);
	boxfill8(vram, xsize, COL8_FFFFFF, 0, ysize - 27, xsize - 1, ysize - 27);
	boxfill8(vram, xsize, COL8_C6C6C6, 0, ysize - 26, xsize - 1, ysize - 1);

	boxfill8(vram, xsize, COL8_FFFFFF, 3, ysize - 24, 59, ysize - 24);
	boxfill8(vram, xsize, COL8_FFFFFF, 2, ysize - 24, 2, ysize - 4);
	boxfill8(vram, xsize, COL8_848484, 3, ysize - 4, 59, ysize - 4);
	boxfill8(vram, xsize, COL8_848484, 59, ysize - 23, 59, ysize - 5);
	boxfill8(vram, xsize, COL8_000000, 2, ysize - 3, 59, ysize - 3);
	boxfill8(vram, xsize, COL8_000000, 60, ysize - 24, 60, ysize - 3);

	boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 24, xsize - 4, ysize - 24);
	boxfill8(vram, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize - 4);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize - 47, ysize - 3, xsize - 4, ysize - 3);
	boxfill8(vram, xsize, COL8_FFFFFF, xsize - 3, ysize - 24, xsize - 3, ysize - 3);
	while (1)
	{
		io_hlt();
	}
}

void init_palette(void) // 初始化调色板
{
	set_palette(0, 15, table_rgb);
	return;
}

void set_palette(int start, int end, unsigned char *rgb) // 设置调色板
{
	int i, eflags;
	eflags = io_load_eflags(); /* 记录中断许可标志的值 */
	io_cli();				   /* 将中断许可标志置为0,禁止中断 */
	io_out8(0x03c8, start);
	for (i = start; i <= end; i++) // 0x03c8,0x03c9这些都是设备号码，固定的
	{
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3; // 指针偏移，感觉用二维数组直接++比较好
	}
	io_store_eflags(eflags); /* 复原中断许可标志 */
	return;
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
	int x, y;
	for (y = y0; y <= y1; y++)
	{
		for (x = x0; x <= x1; x++)
		{
			vram[y * xsize + x] = c;
		}
	}
	return;
}
