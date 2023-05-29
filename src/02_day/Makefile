# makefile 默认动作 启动
default :
	../z_tools/make.exe run

# 文件生成规则

ipl.bin : ipl.nas Makefile
	../z_tools/nask.exe ipl.nas ipl.bin ipl.lst

helloos.img : ipl.bin Makefile
	../z_tools/edimg.exe   imgin:../z_tools/fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0   imgout:helloos.img

# 一般规则

# 将ipl.nas编译成ipl.bin
asm :
	../z_tools/make.exe -r ipl.bin

# 生成img文件
img :
	../z_tools/make.exe -r helloos.img

# 运行
run :
	../z_tools/make.exe img
	copy helloos.img ..\z_tools\qemu\fdimage0.bin
	../z_tools/make.exe -C ../z_tools/qemu

# 写入软盘
install :
	../z_tools/make.exe img
	../z_tools/imgtol.com w a: helloos.img

# 清除中间文件
clean :
	-del ipl.bin
	-del ipl.lst

# 清除所有生成文件 只保留源文件
src_only :
	../z_tools/make.exe clean
	-del helloos.img
