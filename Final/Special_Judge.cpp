#include "define.h"

//��������ж�
void Error(int n) {
	if (1 == n) {
		cout << "����������Ԫ�ظ�������ȷ�����������룡" << endl;
	}
	else if (2 == n) {
		cout << "ִ���ļ�������������������룡" << endl;
	}
	else if (3 == n) {
		cout << "��������������������룡" << endl;
	}
	else if (4 == n) {
		cout << "������������Ƿ������������룡" << endl;
	}
}

bool Input_Judge(int argc, char *argv[]) {
	int flag = 0; //0Ϊ������ȷ��1Ϊ����
	int len = strlen(argv[2]);
	if (3 != argc) {
		Error(1); //���������������3��
		flag = 1;
	}
	/*if (strcmp(argv[0], "F:\\programming\\���\\������̻���\\soduku\\Debug\\soduku.exe")) {
	Error(2);
	flag = 1;
	}*/
	if (strcmp(argv[1], "-c") && strcmp(argv[1], "-s")) {
		Error(3); //�ڶ�����������-c����-s
		flag = 1;
	}
	if (!strcmp(argv[1], "-c")) {
		for (int i = 0; i < len; i++) {
			if (argv[2][i] < '0' || argv[2][i] > '9') {
				Error(4); //�����������ֵ�
				flag = 1;
				break;
			}
		}
	}

	if (!flag) return true;
	else return false;
}

bool VC_Judge(int x, int y, char(&SDmap)[30][30], int col) {
	int num[10] = { 0 }; //�жϸõ����ڵľŹ����Ƿ�����Ҫ��
	bool ans = true;
	int a = x / 3 * 3, b = y / 6 * 6;
	//�жϸõ������к����Ƿ���������
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
	//��ӦС�Ź�����������
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