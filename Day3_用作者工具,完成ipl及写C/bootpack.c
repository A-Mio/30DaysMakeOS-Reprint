/* 告诉C编译器，有一个函数在别的文件里 */

void io_hlt(void);

int HariMain(void)	//就是main函数
{

fin:
	io_hlt(); /* 执行naskfunc.nas中的_io_hlt函数 */
	goto fin;
	return 0;
}
