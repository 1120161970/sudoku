#pragma once
#pragma once
#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

void Error(int n); //������Ϣ����
bool Input_Judge(int argc, char *argv[]); //�����ж�
void CreateNewJGG(char *c, int &pos); //����һ������������
void Function_c(char *argv[]); //����Ϊ-cʱִ��
void Function_s(char *argv[]); //����Ϊ-sʱִ��
bool VC_Judge(int x, int y, char(&SDmap)[30][30], int col); //�ж����������λ�úϲ�����
bool DFS(int x, int y, char(&SDmap)[30][30]); //����
void InitRand(); //΢�뼶�����
