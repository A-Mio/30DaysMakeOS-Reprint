/* asmhead.nas */
// 把一串要用的变量集中起来
struct BOOTINFO
{               /* 0x0ff0-0x0fff */
    char cyls;  /* 启动区读磁盘读到此为止 */
    char leds;  /* 启动时键盘的LED的状态 */
    char vmode; /* 显卡模式为多少位彩色 */
    char reserve;
    short scrnx, scrny; /* 画面分辨率 */
    char *vram;
};
#define ADR_BOOTINFO 0x00000ff0

/* 告诉C编译器，有函数在别的文件里 naskfunc.nas*/
void io_hlt(void);                // 停机
void io_cli(void);                // 禁止中断
void io_sti(void);                // 允许中断
void io_stihlt(void);             // 允许中断和停机
void io_out8(int port, int data); // 将值输出到端口
int io_load_eflags(void);         // 读取中断许可标志的值
void io_store_eflags(int eflags); // 复原中断许可标志

void load_gdtr(int limit, int addr); // 将指定的段上限和地址值赋值给名为GDTR的48位寄存器
void load_idtr(int limit, int addr); // 设置IDTR的值

void asm_inthandler21(void); // 调用键盘中断处理函数
void asm_inthandler27(void); // 其他
void asm_inthandler2c(void); // 调用鼠标中断处理函数
// 用汇编封装的结束

/* fifo.c */
struct FIFO8 // 缓冲
{
    unsigned char *buf;
    int p, q, size, free, flags;
};
void fifo8_init(struct FIFO8 *fifo, int size, unsigned char *buf); // 初始化FIFO缓冲区
int fifo8_put(struct FIFO8 *fifo, unsigned char data);             // 向FIFO传送数据并保存
int fifo8_get(struct FIFO8 *fifo);                                 // 从FIFO取得一个数据
int fifo8_status(struct FIFO8 *fifo);                              // 报告一下积攒是数据量,查看缓冲区状态

/* graphic.c */
void init_palette(void);                                                                        // 初始化调色板
void set_palette(int start, int end, unsigned char *rgb);                                       // 设置调色板
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1); // 画框

void init_screen(char *vram, int x, int y);                                                                // 初始化屏幕
void putfont8(char *vram, int xsize, int x, int y, char c, char *font);                                    // 显示字符
void putfonts8_asc(char *vram, int xsize, int x, int y, char c, unsigned char *s);                         // 显示字符串
void init_mouse_cursor8(char *mouse, char bc);                                                             // 初始化鼠标
void putblock8_8(char *vram, int vxsize, int pxsize, int pysize, int px0, int py0, char *buf, int bxsize); // 显示鼠标

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

/* dsctbl.c */
/*GDT(全局段号记录表)与IDT(中断记录表)相关	*/
/*以CPU的资料为基础*/
struct SEGMENT_DESCRIPTOR // GDT
{
    short limit_low, base_low;
    char base_mid, access_right;
    char limit_high, base_high;
};

struct GATE_DESCRIPTOR // IDT
{
    short offset_low, selector;
    char dw_count, access_right;
    short offset_high;
};

void init_gdtidt(void);                                                                 // GDT、IDT、descriptor table 关系处理
void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar); // GDT的设定
void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar);        // IDT的设定

#define ADR_IDT 0x0026f800
#define LIMIT_IDT 0x000007ff
#define ADR_GDT 0x00270000
#define LIMIT_GDT 0x0000ffff
#define ADR_BOTPAK 0x00280000
#define LIMIT_BOTPAK 0x0007ffff
#define AR_DATA32_RW 0x4092
#define AR_CODE32_ER 0x409a
#define AR_INTGATE32 0x008e

/* int.c */
void init_pic(void);         // 初始化PIC
void inthandler21(int *esp); // 键盘中断处理
void inthandler27(int *esp); // 其他
void inthandler2c(int *esp); // 鼠标中断处理
#define PIC0_ICW1 0x0020
#define PIC0_OCW2 0x0020
#define PIC0_IMR 0x0021
#define PIC0_ICW2 0x0021
#define PIC0_ICW3 0x0021
#define PIC0_ICW4 0x0021
#define PIC1_ICW1 0x00a0
#define PIC1_OCW2 0x00a0
#define PIC1_IMR 0x00a1
#define PIC1_ICW2 0x00a1
#define PIC1_ICW3 0x00a1
#define PIC1_ICW4 0x00a1
