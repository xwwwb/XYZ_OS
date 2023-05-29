# XYZ OS🐧

本仓库负责存储郑州轻工业大学计算机学院操作系统课程设计代码

🥳本项目将依托《30 天自制操作系统》从零开始制作一个操作系统 🎉

| 日期 | 进度             | 备注                                                         |
| ---- | ---------------- | ------------------------------------------------------------ |
| day1 | 已完成 2023-5-28 | 可以调用显卡 BIOS 中断显示字符 🎊Hello World!                 |
| day2 | 已完成 2023-5-28 | 前 512 字节的磁盘文件生成和完整镜像生成，makefile 文件完善 💾disk! |
| day3 | 已完成 2023-5-28 | C 语言导入，从磁盘读入 10 个柱面 🥲 好难                      |
| day4 | 已完成 2023-5-28 | 已经可以基本显示画面了 🥳                                     |
| day5 | 未完成           | ...                                                          |

## 项目结构
```
- src             # 项目代码
  - 01_day
  - 02_day
  - 03_day
  ...
- README.md       # 总介绍文件


- index.html      # 无用 不用关心
- _sidebar.md     # 无用 不用关心
- _coverpage.md   # 无用 不用关心
- image_md        # 图片存储
```

## 实验截图

### 第一天

<img src="./image_md/image-20230529210641118.png" alt="image-20230529210641118" style="zoom:50%;" />

### 第二天

和第一天的运行结果一致：

<img src="./image_md/image-20230529210847550.png" alt="image-20230529210847550" style="zoom:80%;" />

附上VMware的运行结果和裸机运行结果

<img src="./image_md/image-20230529211029376.png" alt="image-20230529211029376" style="zoom:80%;" />

<img src="./image_md/image-20230529211606790.png" alt="image-20230529211606790" style="zoom:80%;" />

### 第三天

可以显示一个黑色的画面 

 <img src="./image_md/image-20230529211242634.png" alt="image-20230529211242634" style="zoom:80%;" />

### 第四天

C语言汇编混合编程 汇编实现了几个函数

这里两个实验结果 使用makefile的变量切换编译的文件

一个是结合了计算机图形学的简单算法绘制图像 直接读写显存

一个是书本的运行结果

<img src="./image_md/image-20230529211428060.png" alt="image-20230529211428060" style="zoom:80%;" />

<img src="./image_md/image-20230529211749295.png" alt="image-20230529211749295" style="zoom:80%;" />
