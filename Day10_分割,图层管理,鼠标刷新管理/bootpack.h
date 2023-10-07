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

void load_idtr(int limit, int addr);
int load_cr0(void);
unsigned int memtest_sub(unsigned int start, unsigned int end);

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

void init_screen8(char *vram, int x, int y);                                                               // 初始化屏幕
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
void inthandler27(int *esp); // 其他
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

/* keyboard.c */
#define PORT_KEYDAT 0x0060 // 编号为0x0060的设备就是键盘，固定
#define PORT_KEYSTA 0x0064
#define PORT_KEYCMD 0x0064
#define KEYSTA_SEND_NOTREADY 0x02
#define KEYCMD_WRITE_MODE 0x60
#define KBC_MODE 0x47
extern struct FIFO8 keyfifo;   // 键盘输入缓冲
void inthandler21(int *esp);   // 来自PS/2键盘的中断
void init_keyboard(void);      // 初始化键盘控制电路
void wait_KBC_sendready(void); // 等待键盘控制电路准备完毕

/* mouse.c */
#define KEYCMD_SENDTO_MOUSE 0xd4
#define MOUSECMD_ENABLE 0xf4
struct MOUSE_DEC // 存放鼠标解读结果
{
    unsigned char buf[3], phase;
    int x, y, btn;
};
extern struct FIFO8 mousefifo;                               // 鼠标输入缓冲
void inthandler2c(int *esp);                                 // 来自PS/2鼠标的中断
void enable_mouse(struct MOUSE_DEC *mdec);                   // 激活鼠标
int mouse_decode(struct MOUSE_DEC *mdec, unsigned char dat); // 鼠标的解读

/* memory.c */
#define MEMMAN_FREES 4090 /* 大约是32KB*/
#define MEMMAN_ADDR 0x003c0000

struct FREEINFO /* 可用信息 */
{
    unsigned int addr, size;
};
struct MEMMAN /* 内存管理 */
{
    int frees, maxfrees, lostsize, losts;
    struct FREEINFO free[MEMMAN_FREES];
};

unsigned int memtest(unsigned int start, unsigned int end);                   // 内存测试
void memman_init(struct MEMMAN *man);                                         // 内存管理初始化
unsigned int memman_total(struct MEMMAN *man);                                // 返回可用内存大小
unsigned int memman_alloc(struct MEMMAN *man, unsigned int size);             // 分配指定大小内存
int memman_free(struct MEMMAN *man, unsigned int addr, unsigned int size);    // 释放内存
unsigned int memman_alloc_4k(struct MEMMAN *man, unsigned int size);          // 以4KB为单位分配
int memman_free_4k(struct MEMMAN *man, unsigned int addr, unsigned int size); // 以4KB为单位释放

/* sheet.c */
#define MAX_SHEETS 256
#define SHEET_USE 1

struct SHEET // 一个图层的信息
{
    unsigned char *buf;
    int bxsize, bysize, vx0, vy0, col_inv, height, flags;
};

struct SHTCTL // 管理多重图层
{
    unsigned char *vram;
    int xsize, ysize, top;
    struct SHEET *sheets[MAX_SHEETS]; // 存放排序好的图层的地址
    struct SHEET sheets0[MAX_SHEETS]; // 存放准备的256个图层信息
};

struct SHTCTL *shtctl_init(struct MEMMAN *memman, unsigned char *vram, int xsize, int ysize);  // 管理图层结构体初始化
struct SHEET *sheet_alloc(struct SHTCTL *ctl);                                                 // 取得新生成的未使用图层
void sheet_setbuf(struct SHEET *sht, unsigned char *buf, int xsize, int ysize, int col_inv);   // 设定图层缓冲区大小和透明色
void sheet_updown(struct SHTCTL *ctl, struct SHEET *sht, int height);                          // 设定高度
void sheet_refresh(struct SHTCTL *ctl, struct SHEET *sht, int bx0, int by0, int bx1, int by1); // 刷新图层
void sheet_slide(struct SHTCTL *ctl, struct SHEET *sht, int vx0, int vy0);                     // 不改变高度只改变xy的刷新
void sheet_free(struct SHTCTL *ctl, struct SHEET *sht);                                        // 释放图层的内存
void sheet_refreshsub(struct SHTCTL *ctl, int vx0, int vy0, int vx1, int vy1);                 // 刷新鼠标覆盖位置
