## 运行方式

直接执行 make.bat

## 代码说明

day5 引入了 GDT 和 IDT，GDT 是全局描述符表，IDT 是中断描述符表，这两个表都是用来描述内存段的，GDT 描述的是内存段的属性，IDT 描述的是中断处理函数的地址。

GDT 和 IDT 的数据结构都是由处理器规定好的

GDT 的首地址要存在 GDTR 寄存器中，IDT 的首地址要存在 IDTR 寄存器中

参考资料

https://blog.csdn.net/chungle2011/article/details/80069703?ydreferer=aHR0cHM6Ly93d3cuZ29vZ2xlLmNvbS8%3D

https://blog.csdn.net/abc123lzf/article/details/109289567

https://www.cnblogs.com/boyxiao/archive/2010/11/20/1882716.html

https://blog.csdn.net/qq_22642239/article/details/70140859

https://www.jianshu.com/p/55f805c8c379

https://zhuanlan.zhihu.com/p/105939886
