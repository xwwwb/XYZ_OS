// 声明一个函数，这个函数的实现在naskfunc.nas中 链接阶段会被链接到一起
void io_hlt(void);

void HariMain(void)
{

fin:
	io_hlt(); /* 执行naskfunc.nas中的_io_hlt函数 */
	goto fin;
}