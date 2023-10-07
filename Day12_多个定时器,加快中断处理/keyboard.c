#include "bootpack.h"

struct FIFO8 keyfifo; // 键盘输入缓冲

void inthandler21(int *esp)
/* 来自PS/2键盘的中断 */
{
    struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
    unsigned char data, s[4];
    io_out8(PIC0_OCW2, 0x61); /* 通知PIC IRQ-01 已经受理完毕 */
    data = io_in8(PORT_KEYDAT);
    fifo8_put(&keyfifo, data);
    return;
}

void wait_KBC_sendready(void)
{
    /* 等待键盘控制电路准备完毕 */
    for (;;)
    {
        if ((io_in8(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0)
        {
            break;
        }
    }
    return;
}

void init_keyboard(void)
{
    /* 初始化键盘控制电路 */
    wait_KBC_sendready();
    io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);
    wait_KBC_sendready();
    io_out8(PORT_KEYDAT, KBC_MODE);
    return;
}