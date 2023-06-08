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

HariMain(void) {
    char *buf;

    int win, i;
    api_initmalloc();
    buf = api_malloc(160 * 160);
    win = api_openwin(buf, 160, 160, -1, "CLOCK");
    int sec = api_getsecond();
    int min = api_getminute();
    int hour = api_gethour();
    int year = api_getyear();
    int mon = api_getmonth();
    int day = api_getday();
    char text[10] = {0};
    sprintf(text, "%02d:%02d:%02d\0", hour, min, sec);
    char text2[12] = {0};
    sprintf(text2, "%04d/%02d/%02d\0", year, mon, day);
    api_putstrwin(win, 28, 27, 0, 11, text);
    api_putstrwin(win, 28, 45, 0, 10, text2);
    api_refreshwin(win, 6, 27, 154, 27 + 40);
    for (;;) {
        if (api_getkey(1) == 0x0a) {
            break; /*按下回车键则break; */
        }
    }
    api_closewin(win);
    api_end();
}
