void io_hlt(void);
void write_mem8(int addr, int data);

void setColor(int x, int y, int color)
{
	int addr = 0xa0000 + x + y * 320;
	write_mem8(addr, color);
}

void drawFullCircle(int x, int y, int color)
{
	int circle_x = 160;
	int circle_y = 100;
	setColor(circle_x + x, circle_y + y, color);
	setColor(circle_x + x, circle_y - y, color);
	setColor(circle_x - x, circle_y + y, color);
	setColor(circle_x - x, circle_y - y, color);
	setColor(circle_x + y, circle_y + x, color);
	setColor(circle_x + y, circle_y - x, color);
	setColor(circle_x - y, circle_y + x, color);
	setColor(circle_x - y, circle_y - x, color);
}

void HariMain(void)
{
	int i;
	int color = 15;
	char *p;
	// 绘制直线
	for (i = 0; i < 320; i++)
	{

		color = color % 16;
		color++;
		p = (char *)(0xa0000 + i + 320 * i);
		*p = color;
	}
	// 绘制矩形上边
	for (i = 0; i < 100; i++)
	{
		color = color % 16;
		color++;
		setColor(20 + i, 20, color);
	}
	// 绘制矩形左边
	for (i = 0; i < 50; i++)
	{
		color = color % 16;
		color++;
		setColor(20, 20 + i, color);
	}
	// 绘制矩形右边
	for (i = 0; i < 50; i++)
	{
		color = color % 16;
		color++;
		setColor(120, 20 + i, color);
	}
	// 绘制矩形下边
	for (i = 0; i < 100; i++)
	{
		color = color % 16;
		color++;
		setColor(20 + i, 70, color);
	}

	int x = 0;
	int y = 50;
	int d = 1 - y;
	while (x < y)
	{
		color = color % 16;
		color++;
		drawFullCircle(x, y, color);
		if (d < 0)
		{
			d = d + 2 * x + 3;
		}
		else
		{
			d = d + 2 * (x - y) + 5;
			y = y - 1;
		}
		x = x + 1;
	}

	for (;;)
	{
		io_hlt();
	}
}
