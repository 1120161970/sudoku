#include "define.h"

//输入错误判断
void Error(int n) {
	if (1 == n) {
		cout << "命令行输入元素个数不正确，请重新输入！" << endl;
	}
	else if (2 == n) {
		cout << "执行文件名输入错误，请重新输入！" << endl;
	}
	else if (3 == n) {
		cout << "参数输入错误，请重新输入！" << endl;
	}
	else if (4 == n) {
		cout << "数独个数输入非法，请重新输入！" << endl;
	}
}

bool Input_Judge(int argc, char *argv[]) {
	int flag = 0; //0为输入正确，1为错误
	int len = strlen(argv[2]);
	if (3 != argc) {
		Error(1); //输入参数个数不是3个
		flag = 1;
	}
	/*if (strcmp(argv[0], "F:\\programming\\大二\\软件工程基础\\soduku\\Debug\\soduku.exe")) {
	Error(2);
	flag = 1;
	}*/
	if (strcmp(argv[1], "-c") && strcmp(argv[1], "-s")) {
		Error(3); //第二个参数不是-c或者-s
		flag = 1;
	}
	if (!strcmp(argv[1], "-c")) {
		for (int i = 0; i < len; i++) {
			if (argv[2][i] < '0' || argv[2][i] > '9') {
				Error(4); //包含不是数字的
				flag = 1;
				break;
			}
		}
	}

	if (!flag) return true;
	else return false;
}

bool VC_Judge(int x, int y, char(&SDmap)[30][30], int col) {
	int num[10] = { 0 }; //判断该点所在的九宫格是否满足要求
	bool ans = true;
	int a = x / 3 * 3, b = y / 6 * 6;
	//判断该点所在行和列是否满足题意
	for (int j = 0; j <= 16; j += 2) {
		if (j != y && SDmap[x][j] == SDmap[x][y]) {
			ans = false;
			return ans;
		}
	}
	for (int i = 0; i <= 8; i++) {
		if (i != x && SDmap[i][y] == SDmap[x][y]) {
			ans = false;
			return ans;
		}
	}
	//对应小九宫格满足题意
	for (int i = a; i < a + 3; i++) {
		for (int j = b; j < b + 5; j += 2) {
			if (i == x && j == y) continue;
			num[SDmap[i][j] - '0'] = 1;
		}
	}
	if (num[col] == 1) {
		ans = false;
		return ans;
	}

	return ans;
}