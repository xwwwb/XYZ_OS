#include <math.h>
#include <stdio.h>
int api_openwin(char *buf, int xsiz, int ysiz, int col_inv, char *title);
void api_initmalloc(void);
char *api_malloc(int size);
void api_refreshwin(int win, int x0, int y0, int x1, int y1);
void api_linewin(int win, int x0, int y0, int x1, int y1, int col);
void api_closewin(int win);
int api_getkey(int mode);
void api_end(void);
void api_putstrwin(int win, int x, int y, int col, int len, char *str);
int api_getsecond(void);
int api_getminute(void);
int api_gethour(void);
int ap_getyear(void);
int api_getmonth(void);
int api_getday(void);
void api_drawcircle(int win, int x, int y, int r, int nouse, int col);
int api_alloctimer(void);
void api_inittimer(int timer, int data);
void api_settimer(int timer, int time);
void api_boxfilwin(int win, int x0, int y0, int x1, int y1, int col);

double M_PI = 3.14;
HariMain(void) {
    char *buf;
    int win, i;
    api_initmalloc();
    buf = api_malloc(160 * 180);
    win = api_openwin(buf, 160, 180, -1, "CLOCK");
    static int label_m[60][2] = {
            {80, 33},
            {86, 33},
            {92, 34},
            {98, 35},
            {104, 38},
            {110, 41},
            {115, 44},
            {120, 48},
            {124, 52},
            {128, 57},
            {131, 62},
            {134, 68},
            {137, 74},
            {138, 80},
            {139, 86},
            {140, 93},
            {139, 99},
            {138, 105},
            {137, 111},
            {134, 117},
            {131, 122},
            {128, 128},
            {124, 133},
            {120, 137},
            {115, 141},
            {110, 144},
            {104, 147},
            {98, 150},
            {92, 151},
            {86, 152},
            {80, 153},
            {73, 152},
            {67, 151},
            {61, 150},
            {55, 147},
            {50, 144},
            {44, 141},
            {39, 137},
            {35, 133},
            {31, 128},
            {28, 123},
            {25, 117},
            {22, 111},
            {21, 105},
            {20, 99},
            {20, 93},
            {20, 86},
            {21, 80},
            {22, 74},
            {25, 68},
            {28, 62},
            {31, 57},
            {35, 52},
            {39, 48},
            {44, 44},
            {50, 41},
            {55, 38},
            {61, 35},
            {67, 34},
            {73, 33}};
    static int label_h[12][2] = {
            {80, 63},
            {95, 67},
            {105, 78},
            {110, 93},
            {105, 108},
            {95, 118},
            {79, 123},
            {65, 118},
            {54, 108},
            {50, 93},
            {54, 78},
            {64, 67}};
    static int label_text[12][2] = {
            {80, 38},
            {107, 45},
            {127, 65},
            {135, 93},
            {127, 120},
            {107, 140},
            {79, 148},
            {52, 140},
            {32, 120},
            {25, 93},
            {32, 65},
            {52, 45}};
    int timer;
    timer = api_alloctimer();
    api_inittimer(timer, 128);
    char *s;
    int sec = 0, min = 0, hou = 0;

    sec = api_getsecond();
    min = api_getminute();
    hou = api_gethour();
    api_boxfilwin(win + 1, 80 - 65, 93 - 65, 80 + 65, 93 + 65, 8);
    // 圆心是80,93，半径是65 表盘
    api_drawcircle(win, 80, 93, 65, 0, 15);
    api_linewin(win + 1, 80, 93, label_m[min][0], label_m[min][1], 0);
    api_linewin(win + 1, 80, 93, label_h[hou % 12][0], label_h[hou % 12][1], 0);
    api_linewin(win + 1, 80, 93, label_m[sec][0], label_m[sec][1], 1);
    int dx = -5, dy = -6;
    for (;;) {
        // 清除原本
        api_boxfilwin(win + 1, 80 - 65, 93 - 65, 80 + 65, 93 + 65, 8);
        // 圆心是80,93，半径是65 表盘
        api_drawcircle(win, 80, 93, 65, 0, 15);
        int i;
        for (i = 0; i < 12; i++) {
            char s[2] = {0};
            int j = (i + 12) % 12;
            if (j == 0) j = 12;
            sprintf(s, "%d", j);
            api_putstrwin(win + 1, label_text[i][0] + dx, label_text[i][1] + dy, 0, 2, s);
        }
        api_linewin(win + 1, 80, 93, label_m[min][0], label_m[min][1], 0);
        api_linewin(win + 1, 80, 93, label_h[hou % 12][0], label_h[hou % 12][1], 0);
        api_linewin(win + 1, 80, 93, label_m[sec][0], label_m[sec][1], 1);

        api_refreshwin(win, 0, 0, 160, 180);

        api_settimer(timer, 100); /* 1秒 */
        if (api_getkey(1) != 128) {
            break;
        }
        sec = api_getsecond();
        min = api_getminute();
        hou = api_gethour();
    }
    api_closewin(win);
    api_end();
}
