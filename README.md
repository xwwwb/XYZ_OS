# XYZ OS🐧

本仓库负责存储郑州轻工业大学计算机学院操作系统课程设计代码

🥳 本项目将依托《30 天自制操作系统》从零开始制作一个操作系统 🎉

| 日期 | 进度             | 备注                                                                                   |
| ---- | ---------------- | -------------------------------------------------------------------------------------- |
| day1 | 已完成 2023-5-28 | 可以调用显卡 BIOS 中断显示字符 🎊Hello World!                                          |
| day2 | 已完成 2023-5-28 | 前 512 字节的磁盘文件生成和完整镜像生成，makefile 文件完善 💾disk!                     |
| day3 | 已完成 2023-5-29 | C 语言导入，从磁盘读入 10 个柱面 🥲 好难                                               |
| day4 | 已完成 2023-5-29 | 已经可以基本显示画面了 🥳 逐渐感觉到有意思了                                           |
| day5 | 已完成 2023-5-31 | 了解了结构体的内存分布和使用，新增的 GDT 和 IDT 部分很迷糊 😫 很晕...                  |
| day6 | 已完成 2023-5-31 | PIC 也很迷糊，中断处理程序作用是保护 CPU 现场，结合 day5 可以理解一点 🤨 很晕...       |
| day7 | 已完成 2023-6-1  | 理解了 FIFO 先进先出的实现，将其应用在处理键盘和鼠标的中断处理中 🥱 相对于前两天好理解 |
| day8 | 已完成 2023-6-1  | 解析鼠标传入的信号，获得点击和移动事件，修改图形显示代码，实现鼠标的移动 🤩 很有成就感 |

## 项目结构

```
- src             # 项目代码
  - 01_day
  - 02_day
  - 03_day
  ...
- README.md       # 总介绍文件

- index.html      # web entry   不用关心
- docs            # web code    不用关心
- image_md        # 图片存储
```

## 疑问

- [ ] 书本 P80-84 调色板部分代码尚未查阅资料理解
- [x] 书本 P100 鼠标背景显示函数的实际意义？ 已解决
- [ ] 书本 P113 LGDT 的计算没看懂
- [ ] 代码 day6 25 26 行没看懂
- [ ] 代码 汇编 OUT 和 IN 是怎么工作的
- [ ] 书本 day5-6 还是由很多疑问 GDT IDT PIC 等
- [ ] 书本 P123 DS 也好 ES 也好 SS 也好 这句话没看懂
- [ ] 书本 day8 的通往 32 位模式的跳转代码没看懂
- [ ] 第十天的叠加处理，看着后面的忘着前面的，抽时间把这部分复习一下
- [ ] 第十一天消除闪烁 算法有些看不懂 主要是第十天的没学扎实
- [ ] 第十二天的加快中断算法 没有看的很懂
- [ ] 第十三天的算法 基本上都看得一知半解 没心情研究了

## 实验截图

### 第一天

<img src="./image_md/image-20230529210641118.png" alt="image-20230529210641118" style="zoom:50%;" />

### 第二天

和第一天的运行结果一致：

<img src="./image_md/image-20230529210847550.png" alt="image-20230529210847550" style="zoom:80%;" />

附上 VMware 的运行结果和裸机运行结果

<img src="./image_md/image-20230529211029376.png" alt="image-20230529211029376" style="zoom:80%;" />

<img src="./image_md/image-20230529211606790.png" alt="image-20230529211606790" style="zoom:80%;" />

### 第三天

可以显示一个黑色的画面

 <img src="./image_md/image-20230529211242634.png" alt="image-20230529211242634" style="zoom:80%;" />

### 第四天

C 语言汇编混合编程 汇编实现了几个函数

这里两个实验结果 使用 makefile 的变量切换编译的文件

一个是结合了计算机图形学的简单算法绘制图像 直接读写显存

一个是书本的运行结果

<img src="./image_md/image-20230529211428060.png" alt="image-20230529211428060" style="zoom:80%;" />

<img src="./image_md/image-20230529211749295.png" alt="image-20230529211749295" style="zoom:80%;" />

### 第五天

结构体在内存中顺序存储，结构体指针指向结构体的首地址，结构体各个元素都可以按顺序用箭头访问到

然后使用了字符点阵的形式表示单个字符，这里对以下输出算法做个简单的例子

```C
int main(){
    static char font_A[16] = {
		0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
		0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00
	};

	putfont8(binfo->vram, binfo->scrnx, 10, 10, COL8_FFFFFF, font_A);
}
void putfont8(char *vram, int xsize, int x, int y, char c, char *font)
{
	int i;
	char *p, d /* data */;
	for (i = 0; i < 16; i++) {
		p = vram + (y + i) * xsize + x;
		d = font[i];
		if ((d & 0x80) != 0) { p[0] = c; }
		if ((d & 0x40) != 0) { p[1] = c; }
		if ((d & 0x20) != 0) { p[2] = c; }
		if ((d & 0x10) != 0) { p[3] = c; }
		if ((d & 0x08) != 0) { p[4] = c; }
		if ((d & 0x04) != 0) { p[5] = c; }
		if ((d & 0x02) != 0) { p[6] = c; }
		if ((d & 0x01) != 0) { p[7] = c; }
	}
	return;
}
```

以上 font_A 存储了 A 字符的点阵信息

<img src="./image_md/image-20230601113822518.png" alt="image-20230601113822518" style="zoom:25%;" />

```
// 对以上代码进行分析
// 13行的for就是循环点阵每一行 16-23的判断就是输出每一行中的每一列
// 以第三行 00011000为例 此时d为0x18 也就是00011000
16行
00011000
10000000
-------- &
00000000
不显示字符

19行
00011000
00010000
-------- &
00010000
显示字符

由此可知
使用按位递减的与操作，可以判断出d的每一位是不是1 从而决定该像素是否被渲染
```

这里将 A 的字符点阵进行修改 倒数第三行全部换成 1

新的 font_A

```c
static char font_A[16] = {
	0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
	0x24, 0x7e, 0x42, 0x42, 0x42, 0xff, 0x00, 0x00
};
```

![image-20230601114415509](./image_md/image-20230601114415509.png)

在第五天我们还研究出如何更改入口函数

是很蹩脚的方法，仅在这里做简单说明，没有找到更好的办法前，还是使用默认的入口函数

在 naskfunc.nas 添加以下语句，声明原本的入口函数后 调用自己的入口函数名称 根据汇编规则前面加\_

为了防止报错 还要 EXTERN 这个标识符 也要把 HariMain 暴漏出去

<img src="./image_md/image-20230601115109731.png" alt="image-20230601115109731" style="zoom:50%;" />

<img src="./image_md/image-20230601115005589.png" alt="image-20230601115005589" style="zoom:60%;" />

### 第六天

第六天主要做了文件分割

将 C 语言分割为多个带源文件和头文件的文件

然后做了 PIC 的初始化可以接收中断

然后使用栈的数据结构做了 CPU 现场保护

即需要调用中断处理程序前，需要保存 CPU 当前寄存器的所有值

调用后恢复所有值 CPU 回到正常运行

具体原理有些难 还在研读中

![image-20230601120007632](./image_md/image-20230601120007632.png)
