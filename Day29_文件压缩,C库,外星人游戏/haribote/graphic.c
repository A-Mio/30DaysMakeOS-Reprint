#include "bootpack.h"

void init_palette(void) // 初始化调色板
{
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
    unsigned char table2[216 * 3];
    int r, g, b;
    set_palette(0, 15, table_rgb);
    for (b = 0; b < 6; b++)
    {
        for (g = 0; g < 6; g++)
        {
            for (r = 0; r < 6; r++)
            {
                table2[(r + g * 6 + b * 36) * 3 + 0] = r * 51;
                table2[(r + g * 6 + b * 36) * 3 + 1] = g * 51;
                table2[(r + g * 6 + b * 36) * 3 + 2] = b * 51;
            }
        }
    }
    set_palette(16, 231, table2);
    return;
}

void set_palette(int start, int end, unsigned char *rgb) // 设置调色板
{
    int i, eflags;
    eflags = io_load_eflags(); /* 记录中断许可标志的值 */
    io_cli();                  /* 将中断许可标志置为0,禁止中断 */
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

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1) // 画框
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

void init_screen8(char *vram, int x, int y) // 初始化屏幕
{
    boxfill8(vram, x, COL8_008484, 0, 0, x - 1, y - 29);
    boxfill8(vram, x, COL8_C6C6C6, 0, y - 28, x - 1, y - 28);
    boxfill8(vram, x, COL8_FFFFFF, 0, y - 27, x - 1, y - 27);
    boxfill8(vram, x, COL8_C6C6C6, 0, y - 26, x - 1, y - 1);

    boxfill8(vram, x, COL8_FFFFFF, 3, y - 24, 59, y - 24);
    boxfill8(vram, x, COL8_FFFFFF, 2, y - 24, 2, y - 4);
    boxfill8(vram, x, COL8_848484, 3, y - 4, 59, y - 4);
    boxfill8(vram, x, COL8_848484, 59, y - 23, 59, y - 5);
    boxfill8(vram, x, COL8_000000, 2, y - 3, 59, y - 3);
    boxfill8(vram, x, COL8_000000, 60, y - 24, 60, y - 3);

    boxfill8(vram, x, COL8_848484, x - 47, y - 24, x - 4, y - 24);
    boxfill8(vram, x, COL8_848484, x - 47, y - 23, x - 47, y - 4);
    boxfill8(vram, x, COL8_FFFFFF, x - 47, y - 3, x - 4, y - 3);
    boxfill8(vram, x, COL8_FFFFFF, x - 3, y - 24, x - 3, y - 3);
    return;
}

void putfont8(char *vram, int xsize, int x, int y, char c, char *font) // 显示字符
{
    int i;
    char *p, d /* data */;
    for (i = 0; i < 16; i++)
    {
        p = vram + (y + i) * xsize + x;
        d = font[i];
        if ((d & 0x80) != 0)
        {
            p[0] = c;
        }
        if ((d & 0x40) != 0)
        {
            p[1] = c;
        }
        if ((d & 0x20) != 0)
        {
            p[2] = c;
        }
        if ((d & 0x10) != 0)
        {
            p[3] = c;
        }
        if ((d & 0x08) != 0)
        {
            p[4] = c;
        }
        if ((d & 0x04) != 0)
        {
            p[5] = c;
        }
        if ((d & 0x02) != 0)
        {
            p[6] = c;
        }
        if ((d & 0x01) != 0)
        {
            p[7] = c;
        }
    }
    return;
}

void putfonts8_asc(char *vram, int xsize, int x, int y, char c, unsigned char *s) // 显示字符串
{
    extern char hankaku[4096];
    struct TASK *task = task_now();
    char *nihongo = (char *)*((int *)0x0fe8), *font;
    int k, t;

    if (task->langmode == 0)
    {
        for (; *s != 0x00; s++)
        {
            putfont8(vram, xsize, x, y, c, hankaku + *s * 16);
            x += 8;
        }
    }
    if (task->langmode == 1)
    {
        for (; *s != 0x00; s++)
        {
            if (task->langbyte1 == 0)
            {
                if ((0x81 <= *s && *s <= 0x9f) || (0xe0 <= *s && *s <= 0xfc))
                {
                    task->langbyte1 = *s;
                }
                else
                {
                    putfont8(vram, xsize, x, y, c, nihongo + *s * 16);
                }
            }
            else
            {
                if (0x81 <= task->langbyte1 && task->langbyte1 <= 0x9f)
                {
                    k = (task->langbyte1 - 0x81) * 2;
                }
                else
                {
                    k = (task->langbyte1 - 0xe0) * 2 + 62;
                }
                if (0x40 <= *s && *s <= 0x7e)
                {
                    t = *s - 0x40;
                }
                else if (0x80 <= *s && *s <= 0x9e)
                {
                    t = *s - 0x80 + 63;
                }
                else
                {
                    t = *s - 0x9f;
                    k++;
                }
                task->langbyte1 = 0;
                font = nihongo + 256 * 16 + (k * 94 + t) * 32;
                putfont8(vram, xsize, x - 8, y, c, font);  /* 左半部分 */
                putfont8(vram, xsize, x, y, c, font + 16); /* 右半部分 */
            }
            x += 8;
        }
    }
    if (task->langmode == 2)
    {
        for (; *s != 0x00; s++)
        {
            if (task->langbyte1 == 0)
            {
                if (0x81 <= *s && *s <= 0xfe)
                {
                    task->langbyte1 = *s;
                }
                else
                {
                    putfont8(vram, xsize, x, y, c, nihongo + *s * 16);
                }
            }
            else
            {
                k = task->langbyte1 - 0xa1;
                t = *s - 0xa1;
                task->langbyte1 = 0;
                font = nihongo + 256 * 16 + (k * 94 + t) * 32;
                putfont8(vram, xsize, x - 8, y, c, font);  /* 左半部分 */
                putfont8(vram, xsize, x, y, c, font + 16); /* 右半部分 */
            }
            x += 8;
        }
    }
    if (task->langmode == 3)
    {
        for (; *s != 0x00; s++)
        {
            if (task->langbyte1 == 0)
            {
                if (0xa1 <= *s && *s <= 0xfe)
                {
                    task->langbyte1 = *s;
                }
                else
                {
                    // putfont8(vram, xsize, x, y, c, nihongo + *s * 16);
                    putfont8(vram, xsize, x, y, c, hankaku + *s * 16);
                }
            }
            else
            {
                k = task->langbyte1 - 0xa1;
                t = *s - 0xa1;
                task->langbyte1 = 0;
                font = nihongo + 256 * 16 + 32 * 94 * 47 + (k * 94 + t) * 32;

                unsigned char New[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                unsigned char New2[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                int i;

                for (i = 0; i <= 7; i++) /* 取上半边数据 */
                {
                    New[i] = font[i * 2];        /* 左半角取偶数位置字节 */
                    New2[i] = (font)[2 * i + 1]; /* 右半角取奇数位置字节 */
                }

                for (i = 8; i <= 15; i++) /* 取下半边数据 */
                {
                    New[i] = (font + 16)[(i - 8) * 2];
                    New2[i] = (font + 16)[(i - 8) * 2 + 1];
                }

                putfont8(vram, xsize, x - 8, y, c, New); /* 左半角 */
                putfont8(vram, xsize, x, y, c, New2);    /* 右半角 */
            }
            x += 8;
        }
    }
    return;
}

void init_mouse_cursor8(char *mouse, char bc) // 初始化鼠标
/*准备鼠标光标（16×16）*/
{
    static char cursor[16][16] = {
        "**************..",
        "*OOOOOOOOOOO*...",
        "*OOOOOOOOOO*....",
        "*OOOOOOOOO*.....",
        "*OOOOOOOO*......",
        "*OOOOOOO*.......",
        "*OOOOOOO*.......",
        "*OOOOOOOO*......",
        "*OOOO**OOO*.....",
        "*OOO*..*OOO*....",
        "*OO*....*OOO*...",
        "*O*......*OOO*..",
        "**........*OOO*.",
        "*..........*OOO*",
        "............*OO*",
        ".............***"};
    int x, y;

    for (y = 0; y < 16; y++)
    {
        for (x = 0; x < 16; x++)
        {
            if (cursor[y][x] == '*')
            {
                mouse[y * 16 + x] = COL8_000000;
            }
            if (cursor[y][x] == 'O')
            {
                mouse[y * 16 + x] = COL8_FFFFFF;
            }
            if (cursor[y][x] == '.')
            {
                mouse[y * 16 + x] = bc;
            }
        }
    }
    return;
}

void putblock8_8(char *vram, int vxsize, int pxsize, int pysize, int px0, int py0, char *buf, int bxsize) // 显示鼠标
{
    int x, y;
    for (y = 0; y < pysize; y++)
    {
        for (x = 0; x < pxsize; x++)
        {
            vram[(py0 + y) * vxsize + (px0 + x)] = buf[y * bxsize + x];
        }
    }
    return;
}
