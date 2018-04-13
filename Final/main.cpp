#include "define.h"

extern char JGG[30][30];
extern char Output_C[250000000]; //生成数独时用于存所有数独的数组

int main(int argc, char *argv[]) {
	InitRand(); //初始化随机数种子
	bool ans = Input_Judge(argc, argv); //输入判断
	if (ans == false) return 0;
	if (!strcmp(argv[1], "-c")) {
		Function_c(argv);
	}
	else if (!strcmp(argv[1], "-s")) {
		Function_s(argv);
	}

	return 0;
}