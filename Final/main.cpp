#include "define.h"

extern char JGG[30][30];
extern char Output_C[250000000]; //��������ʱ���ڴ���������������

int main(int argc, char *argv[]) {
	InitRand(); //��ʼ�����������
	bool ans = Input_Judge(argc, argv); //�����ж�
	if (ans == false) return 0;
	if (!strcmp(argv[1], "-c")) {
		Function_c(argv);
	}
	else if (!strcmp(argv[1], "-s")) {
		Function_s(argv);
	}

	return 0;
}