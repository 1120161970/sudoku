#include "define.h"

char JGG[30][30] = { 0 };
char Output_C[250000000] = { 0 };
char Permutation[10] = { '1','2','3','4','5','6','7','9' }; //组合数

void CreateNewJGG(char *c, int &pos) {
	for (int i = 0; i < 3; i++) {
		Output_C[pos++] = Permutation[(8 + c[i] - '0') % 9];
		for (int j = 1; j < 9; j++) {
			Output_C[pos++] = ' ';
			Output_C[pos++] = Permutation[(8 - j + c[i] - '0') % 9];
		}
		Output_C[pos++] = '\n';
	}
}

void Function_c(char *argv[]) {
	//每三行交换
	char Combinatory1[8][4] = { "036","063" };
	char Combinatory2[8][4] = { "258","285","528","582","825","852" };
	char Combinatory3[8][4] = { "147","174","417","471","714","741" };
	int Shu_du_num = atoi(argv[2]); //数量
	FILE *p = fopen("sudoku.txt", "w");
	bool ans, sn = true;
	int start, end; //起始和结束时间
	int pos = 0, NumofJGG = 0;
	start = clock();
	while (1) {
		Permutation[8] = '8'; //学号标志位
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 6; j++) {
				for (int k = 0; k < 6; k++) {
					CreateNewJGG(Combinatory1[i], pos);
					CreateNewJGG(Combinatory2[j], pos);
					CreateNewJGG(Combinatory3[k], pos);
					Output_C[pos++] = '\n';
					NumofJGG++;
					if (NumofJGG == Shu_du_num) {
						sn = false;
						break;
					}
				}
				if (sn == false) break;
			}
			if (sn == false) break;
		}
		if (sn == false) break;
		next_permutation(Permutation, Permutation + 8); //组合排列，加快数独生成
	}
	fputs(Output_C, p);
	fclose(p);
	end = clock();
	cout << "耗费的时间" << end - start << "毫秒" << endl;
}

void Function_s(char *argv[]) {
	//需要修改，功能其实和那边不太一样
	char Filename[50] = { 0 }, temc;
	strcpy(Filename, argv[2]);
	FILE *p = fopen(argv[2], "r");
	FILE *q = fopen("Solving_ShuDu.txt", "w");
	bool ans, sn;
	int start, end;
	start = clock();
	//
	while (1) {
		for (int i = 0; i < 9; i++) {
			fgets(JGG[i], 20, p);
		}
		temc = fgetc(p); 

		ans = DFS(0, 0, JGG); //从第一个数开始搜索
		if (ans == true) {
			for (int i = 0; i <= 8; i++) {
				for (int j = 0; j <= 16; j++) {
					fprintf(q, (j < 16) ? "%c" : "%c\n", JGG[i][j]);
				}
			}
			fprintf(q, "\n");
			//cout << "输出成功！" << endl;
		}
		else {
			cout << "bugbugbug!" << endl;
		}
		if (temc == EOF) break; //读入文件尾就直接弹出
	}
	end = clock();
	cout << "耗费的时间" << end - start << "毫秒" << endl;
}

bool DFS(int x, int y, char(&SDmap)[30][30]) {
	int vis[10] = { 0 }; //标志当前位
	char ch;
	bool ans, flag;
	//不是0就直接往后走
	if (SDmap[x][y] != '0' && SDmap[x][y] != '\0') {
		if (x == 8 && y == 16) return true; //到最后一位返回成功
		ans = DFS((y + 2 > 16) ? x + 1 : x, (y + 2 > 16) ? 0 : y % 16 + 2, SDmap);
		if (ans == true) return true;
		else return false;
	}
	while (1) {
		int num = rand() % 9;
		num = num % 9 + 1;
		flag = false;
		ch = num + '0';
		SDmap[x][y] = ch;
		if (VC_Judge(x, y, SDmap, num) == false || vis[num]) {
			vis[num] = 1;
			SDmap[x][y] = '0';
		}
		else {
			if (x == 8 && y == 16) {
				return true;
			}
			vis[num] = 1;
			ans = DFS((y + 2 > 16) ? x + 1 : x, (y + 2) % 16, SDmap);
			if (ans == true) {
				flag = true;
				break;
			}
			else {
				SDmap[x][y] = '0';
			}
		}
		//如果当前位置不符合，就搜一下看看本位置还能否放置其余的数字
		//如果不行，就直接返回失败
		for (int i = 1; i <= 9; i++) {
			if (!vis[i]) {
				flag = true;
				break;
			}
			else flag = false;
		}
		if (flag == false) {
			break;
		}
	}
	if (flag == true) return true;
	else return false;
}

void InitRand() {
	LARGE_INTEGER nFrequency;
	if (::QueryPerformanceFrequency(&nFrequency)) {
		LARGE_INTEGER nStartCounter;
		::QueryPerformanceCounter(&nStartCounter);
		::srand((unsigned)nStartCounter.LowPart);
	}
	else {
		srand((unsigned)time(NULL));
	}
}