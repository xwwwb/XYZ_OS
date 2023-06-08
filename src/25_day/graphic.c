/* 关于绘图部分的处理 */

#include "bootpack.h"

void init_palette(void) {
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
    for (b = 0; b < 6; b++) {
        for (g = 0; g < 6; g++) {
            for (r = 0; r < 6; r++) {
                table2[(r + g * 6 + b * 36) * 3 + 0] = r * 51;
                table2[(r + g * 6 + b * 36) * 3 + 1] = g * 51;
                table2[(r + g * 6 + b * 36) * 3 + 2] = b * 51;
            }
        }
    }
    set_palette(16, 231, table2);
    return;
}

void set_palette(int start, int end, unsigned char *rgb) {
    int i, eflags;
    eflags = io_load_eflags(); /* 记录中断许可标志的值 */
    io_cli();                  /* 将中断许可标志置为0,禁止中断 */
    io_out8(0x03c8, start);
    for (i = start; i <= end; i++) {
        io_out8(0x03c9, rgb[0] / 4);
        io_out8(0x03c9, rgb[1] / 4);
        io_out8(0x03c9, rgb[2] / 4);
        rgb += 3;
    }
    io_store_eflags(eflags); /* 复原中断许可标志 */
    return;
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1) {
    int x, y;
    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++)
            vram[y * xsize + x] = c;
    }
    return;
}

void init_screen8(char *vram, int x, int y) {
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

    boxfill8(vram, x, COL8_848484, x - 180, y - 24, x - 4, y - 24);
    boxfill8(vram, x, COL8_848484, x - 180, y - 23, x - 180, y - 4);
    boxfill8(vram, x, COL8_FFFFFF, x - 180, y - 3, x - 4, y - 3);
    boxfill8(vram, x, COL8_FFFFFF, x - 3, y - 24, x - 3, y - 3);
    return;
}

void putfont8(char *vram, int xsize, int x, int y, char c, char *font) {
    int i;
    char *p, d /* data */;
    for (i = 0; i < 16; i++) {
        p = vram + (y + i) * xsize + x;
        d = font[i];
        if ((d & 0x80) != 0) {
            p[0] = c;
        }
        if ((d & 0x40) != 0) {
            p[1] = c;
        }
        if ((d & 0x20) != 0) {
            p[2] = c;
        }
        if ((d & 0x10) != 0) {
            p[3] = c;
        }
        if ((d & 0x08) != 0) {
            p[4] = c;
        }
        if ((d & 0x04) != 0) {
            p[5] = c;
        }
        if ((d & 0x02) != 0) {
            p[6] = c;
        }
        if ((d & 0x01) != 0) {
            p[7] = c;
        }
    }
    return;
}
void putfonts8_asc(char *vram, int xsize, int x, int y, char c, unsigned char *s) {
    extern char hankaku[4096];
    /* C语言中，字符串都是以0x00结尾 */
    for (; *s != 0x00; s++) {
        putfont8(vram, xsize, x, y, c, hankaku + *s * 16);
        x += 8;
    }
    return;
}


void putfont16(char *vram, int xsize, int x, int y, char c, char font[16][16]) {
    // 传入font是16*16的数组
    int i, j;
    char *p, d /* data */;
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            p = vram + (y + i) * xsize + x + j;
            d = font[i][j];
            if (d == '1') {
                p[0] = c;
            }
        }
    }
    return;
}


void init_mouse_cursor8(char *mouse, char bc)
/* 鼠标的数据准备（16x16） */
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

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            if (cursor[y][x] == '*') {
                mouse[y * 16 + x] = COL8_000000;
            }
            if (cursor[y][x] == 'O') {
                mouse[y * 16 + x] = COL8_FFFFFF;
            }
            if (cursor[y][x] == '.') {
                mouse[y * 16 + x] = bc;
            }
        }
    }
    return;
}

void putblock8_8(char *vram, int vxsize, int pxsize,
                 int pysize, int px0, int py0, char *buf, int bxsize) {
    int x, y;
    for (y = 0; y < pysize; y++) {
        for (x = 0; x < pxsize; x++) {
            vram[(py0 + y) * vxsize + (px0 + x)] = buf[y * bxsize + x];
        }
    }
    return;
}

char *getzhfont(int c) {
    static char font_1[16][16] = {
            "0000000000000000",
            "0100001100000000",
            "0110011001111110",
            "0011010001111110",
            "1111111101100110",
            "1111111101100110",
            "0001100001101100",
            "0001100001101000",
            "1111111101101100",
            "1111111101100110",
            "0001100001100110",
            "0001110001100110",
            "0011011001111110",
            "0110001101101100",
            "1100000101100000",
            "1000000001100000",
    };
    static char font_2[16][16] = {
            "0000000000000000",
            "0001100000001100",
            "0001100110001100",
            "0001100110001100",
            "0001100110001100",
            "0101100110001100",
            "0101110111001100",
            "0101110111001100",
            "1101101110101100",
            "1001101110101100",
            "1001100110001100",
            "0001100110001100",
            "0011000110001100",
            "0011000110001100",
            "0110000110001100",
            "0110000000001100"};
    static char font_3[16][16] = {
            "0000000000000000",
            "0011000000000000",
            "0011000111111000",
            "1111110111111000",
            "1111110000011000",
            "0110000000110000",
            "0101100001111000",
            "1101100111001110",
            "1111110110000010",
            "1111110011111100",
            "0001100011111100",
            "0001111000110000",
            "1111111000110000",
            "1111100000110000",
            "0001100111111110",
            "0001100111111110"};
    static char font_4[16][16] = {
            "0000000000000000",
            "0000000000000000",
            "0000000000000000",
            "0011111111111100",
            "0011111111111100",
            "0000000110000000",
            "0000000110000000",
            "0000000110000000",
            "0000000110000000",
            "0000000110000000",
            "0000000110000000",
            "0000000110000000",
            "0000000110000000",
            "0000000110000000",
            "0111111111111110",
            "0111111111111110"};
    static char font_5[16][16] = {
            "0000000000000000",
            "0000011011000000",
            "0000011011000000",
            "0000011011000000",
            "0000011011000000",
            "0110011011001100",
            "0110011011001100",
            "0110011011001100",
            "0011011011011000",
            "0011011011011000",
            "0011011011011000",
            "0000011011000000",
            "0000011011000000",
            "0000011011000000",
            "1111111111111110",
            "1111111111111110",
    };
    static char font_6[16][16] = {
            "0000000000000000",
            "0000001100000000",
            "0000001100000000",
            "0000001100000000",
            "0000001100000000",
            "0111111111111100",
            "0111111111111100",
            "0000001100000000",
            "0000001100000000",
            "0000001100000000",
            "0000011110000000",
            "0000011011000000",
            "0000110001100000",
            "0001100000110000",
            "0011000000011000",
            "0110000000001100"};
    static char font_7[16][16] = {
            "0000000000000000",
            "0011001100011000",
            "0001100110011000",
            "0000100010110000",
            "0111111111111100",
            "0111111111111100",
            "0110000000001100",
            "0001111111110000",
            "0001111111110000",
            "0000000011000000",
            "0111111111111100",
            "0111111111111100",
            "0000000110000000",
            "0000000110000000",
            "0000011110000000",
            "0000001100000000"};
    if (c == 1) {
        return (char *) font_1;
    }
    else if (c == 2) {
        return (char *) font_2;
    }
    else if (c == 3) {
        return (char *) font_3;
    }
    else if (c == 4) {
        return (char *) font_4;
    }
    else if (c == 5) {
        return (char *) font_5;
    }
    else if (c == 6) {
        return (char *) font_6;
    }
    else if (c == 7) {
        return (char *) font_7;
    }
    else {
        return (char *) font_1;
    }
}