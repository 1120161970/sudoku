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

void Error(int n); //输入信息有误
bool Input_Judge(int argc, char *argv[]); //输入判断
void CreateNewJGG(char *c, int &pos); //生成一个数独的三行
void Function_c(char *argv[]); //输入为-c时执行
void Function_s(char *argv[]); //输入为-s时执行
bool VC_Judge(int x, int y, char(&SDmap)[30][30], int col); //判断这个点放这个位置合不合适
bool DFS(int x, int y, char(&SDmap)[30][30]); //搜索
void InitRand(); //微秒级随机数
