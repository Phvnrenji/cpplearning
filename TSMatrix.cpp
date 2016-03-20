//============================================================================
// Name        : Array2D.cpp
// Author      : Dvnean
// Version     :
// Copyright   : Your copyright notice
// Description : 用三元组的数据结构进行稀疏矩阵的压缩
//				   以及编写算法，实现稀疏矩阵的加法和乘法运算
//============================================================================

#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

typedef int elemtype;
const int MAXSIZE = 100;
const int MAXROW = 10;

typedef struct{
	int i, j;	// row and col
	elemtype e;
}Triple;	//定义三元组类型

typedef struct{
	Triple data[MAXSIZE+1];
	int mu;	//行数
	int nu;	//列数
	int tu;	//非零元素个数
}TSMatrix;	//定义稀疏矩阵类型

typedef struct{
	Triple data[MAXSIZE+2];
	int rpos[MAXROW+1];
	int mu, nu, tu;
}RLSMatrix;	//定义带链接信息的三元组类型

void InputTSMatrix(TSMatrix &M);
void OutputTSMatrix(TSMatrix M);

int main() {
//	cout << "!!!Hello World!!!" << endl;
	TSMatrix M;
	InputTSMatrix(M);
	return 0;
}

void InputTSMatrix(TSMatrix &M){
	TSMatrix matrix = M;
	cout << "输入矩阵的行数、列数和元素个数：" << endl;
	cin >> matrix.mu >> matrix.mu >> matrix.tu;
	cout << "输入各非零元素的位置和值：" << endl;
	for(int k = 1; k <= matrix.tu; ++k){
		cin >> matrix.data[k].i >> matrix.data[k].j >>matrix.data[k].e;
	}
	cout << "输入完成！\n" << "稀疏矩阵为：\n";
	OutputTSMatrix(matrix);
}

void OutputTSMatrix(TSMatrix M){
	int m, n, k = 1;
	for(m = 0; m < M.mu; ++m){
		for(n = 0; n < M.nu; ++n){
			if((M.data[k].i - 1) == m && (M.data[k].j - 1) == n){
				cout.width(4);
				cout << M.data[k].e;
                k++;
			}
			else{
				cout.width(4);
				cout << "0";
			}
		}
		cout << endl;
	}
}
