#include "define.h"

char JGG[30][30] = { 0 };
char Output_C[250000000] = { 0 };
char Permutation[10] = { '1','2','3','4','5','6','7','9' }; //�����

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
	//ÿ���н���
	char Combinatory1[8][4] = { "036","063" };
	char Combinatory2[8][4] = { "258","285","528","582","825","852" };
	char Combinatory3[8][4] = { "147","174","417","471","714","741" };
	int Shu_du_num = atoi(argv[2]); //����
	FILE *p = fopen("sudoku.txt", "w");
	bool ans, sn = true;
	int start, end; //��ʼ�ͽ���ʱ��
	int pos = 0, NumofJGG = 0;
	start = clock();
	while (1) {
		Permutation[8] = '8'; //ѧ�ű�־λ
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
		next_permutation(Permutation, Permutation + 8); //������У��ӿ���������
	}
	fputs(Output_C, p);
	fclose(p);
	end = clock();
	cout << "�ķѵ�ʱ��" << end - start << "����" << endl;
}

void Function_s(char *argv[]) {
	//��Ҫ�޸ģ�������ʵ���Ǳ߲�̫һ��
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

		ans = DFS(0, 0, JGG); //�ӵ�һ������ʼ����
		if (ans == true) {
			for (int i = 0; i <= 8; i++) {
				for (int j = 0; j <= 16; j++) {
					fprintf(q, (j < 16) ? "%c" : "%c\n", JGG[i][j]);
				}
			}
			fprintf(q, "\n");
			//cout << "����ɹ���" << endl;
		}
		else {
			cout << "bugbugbug!" << endl;
		}
		if (temc == EOF) break; //�����ļ�β��ֱ�ӵ���
	}
	end = clock();
	cout << "�ķѵ�ʱ��" << end - start << "����" << endl;
}

bool DFS(int x, int y, char(&SDmap)[30][30]) {
	int vis[10] = { 0 }; //��־��ǰλ
	char ch;
	bool ans, flag;
	//����0��ֱ��������
	if (SDmap[x][y] != '0' && SDmap[x][y] != '\0') {
		if (x == 8 && y == 16) return true; //�����һλ���سɹ�
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
		//�����ǰλ�ò����ϣ�����һ�¿�����λ�û��ܷ�������������
		//������У���ֱ�ӷ���ʧ��
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