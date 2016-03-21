//============================================================================
// Name        : TSMatrix.cpp
// Author      : Dvnean
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : 用三元组的数据结构进行稀疏矩阵的压缩
//				 以及编写算法，实现稀疏矩阵的加法和乘法运算
//============================================================================

#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

typedef int elemtype;
const int MAXSIZE = 20;
const int MAXROW = 10;

typedef struct{
	int i, j;	// row and col
	elemtype e;
}Triple;	//定义三元组类型

// typedef struct{
// 	Triple data[MAXSIZE+1];
// 	int mu;	//行数
// 	int nu;	//列数
// 	int tu;	//非零元素个数
// }TSMatrix;	//定义稀疏矩阵类型

typedef struct{
	Triple data[MAXSIZE+2];
	int rpos[MAXROW+1];
	int mu, nu, tu;
}RLSMatrix;	//定义带链接信息的三元组类型

// void InputTSMatrix(TSMatrix &M);
// void OutputTSMatrix(TSMatrix M);
// void TransposeSMatrix(TSMatrix M, TSMatrix &T);
RLSMatrix InputRLSMatrix();
void OutputRLSMatrix(RLSMatrix M);
void TransposeRLSMatrix(RLSMatrix M, RLSMatrix &T);
int MultRLSMatrix();
void CountPosOfTu(RLSMatrix &M);

int main() {
//	cout << "!!!Hello World!!!" << endl;
//	TSMatrix M;
//	InputTSMatrix(M);
//  TransposeSMatrix(M, T);
    int reval;
    reval = MultRLSMatrix();
    if(reval == -1)
        cout << "被乘矩阵的列数不等于乘矩阵的行数，不能相乘" << endl;
    if(reval == 1)
        cout << "OverSize" << endl;
	return 0;
}

int MultRLSMatrix(){
    RLSMatrix Mcand, Mer, Result;
    Mcand = InputRLSMatrix();
    Mer = InputRLSMatrix();
    CountPosOfTu(Mcand);
    CountPosOfTu(Mer);
    if(Mcand.nu ! = Mer.mu)
        return -1;
    Result.mu = Mcand.mu;
    Result.nu = Mer.nu;
    Result.tu = 0;      //初始化
    int temp_value[MAXROW + 1];
    int Mcand_row, Mer_row, current_col;
    int p, q, tp, t;
    if(Mcand.tu * Mer.tu){  //否则乘积为零矩阵
        for(Mcand_row = 1; Mcand_row <= Mcand.mu; ++Mcand_row){
            //累加器清零
            for(int i = 1; i <= Mer.nu; ++i){
                temp_value[i] = 0;
            }//每行结果最大元素数为被乘矩阵的列数
           
            Result.rpos[Mcand_row] = Result.tu + 1; //当前行首个非零元素在三元组中的位置
            
            if(Mcand_row < Mcand.mu){  
                tp = Mcand.rpos[Mcand_row + 1];
            }
            else{
                tp = Mcand.tu + 1;  
            }   //当前行非零元素在三元组第tp个位置之前
            for(p = Mcand.rpos[Mcand_row]; p < tp; ++p){    //对当前行每个元素依次操作
                Mer_row = Mcand.data[p].j;  //当前操作数据在矩阵的列号，对应要与另一矩阵的该行号的数据相乘
                if(Mer_row < Mer.mu){
                    t = Mer.rpos[Mer_row + 1];
                }
                else{
                    t = Mer.tu + 1;
                }   //同上，位置信息
                for(q = Mer.rpos[Mer_row]; q < t; ++q){ 
                    current_col = Mer.data[q].j;
                    temp_value[current_col] += Mcand.data[p].e * Mer.data[q].e;
                }
            }
            for(current_col = 1; current_col <= Result.nu; ++current_col){
                if(temp_value[current_col]){    //辅助数组，不为零时执行
                    if (++Result.tu > MAXSIZE)
                        return 1;
                    Result.data[Result.tu].e = temp_value[current_col];
                    Result.data[Result.tu].i = Mcand_row;
                    Result.data[Result.tu].j = current_col;
                }   //压缩数据到Result三元组中
            }
        }
    }      
    OutputRLSMatrix(Result);
    return 0;
}

void CountPosOfTu(RLSMatrix &M){
    int num[MAXROW + 1];
    for(int col = 1; col <= M.mu; ++col)
        num[col] = 0;   //数组前M.mu个数据初始化为0
    for(int col = 1; col <= M.tu; ++col)
        ++num[T.data[col].i];   //num数组下标对应矩阵行数，内容对应该行非零元素个数
    M.rpos[1] = 1;  //三元组第一个位置
    for(int i = 2; i <= M.mu; ++i)
        M.rpos[i] = M.rpos[i - 1] + num[i - 1];
}//每行第一个非零元素在三元组中的位置


//创建普通三元组矩阵
// void InputTSMatrix(TSMatrix &M){
// 	TSMatrix T;
//     TSMatrix matrix = M;
// 	cout << "输入矩阵的行数、列数和元素个数：" << endl;
// 	cin >> matrix.mu >> matrix.nu >> matrix.tu;
// 	cout << "输入各非零元素的位置和值：" << endl;
// 	for(int k = 1; k <= matrix.tu; ++k){
// 		cin >> matrix.data[k].i >> matrix.data[k].j >>matrix.data[k].e;
// 	}
// 	cout << "输入完成！\n" << "稀疏矩阵为：\n";
// 	OutputTSMatrix(matrix);
//     TransposeSMatrix(matrix, T);
// }


//创建带链接信息的三元组
RLSMatrix InputRLSMatrix(){
	RLSMatrix T;
    RLSMatrix matrix;
	cout << "输入矩阵的行数、列数和元素个数：" << endl;
	cin >> matrix.mu >> matrix.nu >> matrix.tu;
	cout << "输入各非零元素的位置和值：" << endl;
	for(int k = 1; k <= matrix.tu; ++k){
		cin >> matrix.data[k].i >> matrix.data[k].j >>matrix.data[k].e;
	}
	cout << "输入完成！\n" << "稀疏矩阵为：\n";
	OutputRLSMatrix(matrix);
    TransposeRLSMatrix(matrix, T);
    return matrix;
}

//输出带链接信息的三元组矩阵
void OutputRLSMatrix(RLSMatrix M){
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

//输出普通三元组矩阵
// void OutputTSMatrix(TSMatrix M){
// 	int m, n, k = 1;
// 	for(m = 0; m < M.mu; ++m){
// 		for(n = 0; n < M.nu; ++n){
// 			if((M.data[k].i - 1) == m && (M.data[k].j - 1) == n){
// 				cout.width(4);
// 				cout << M.data[k].e;
//                 k++;
// 			}
// 			else{
// 				cout.width(4);
// 				cout << "0";
// 			}
// 		}
// 		cout << endl;
// 	}
// }

void TransposeRLSMatrix(RLSMatrix M, RLSMatrix &T){
    // TSMatrix matrix;
    int num[MAXROW + 1];
    int cpot[MAXROW + 1]; //   构建辅助数组
    int q, p, t;
    T.tu = M.tu;
    T.mu = M.nu;
    T.nu = M.mu;
    if (T.tu) {
        for (int col = 1; col <= M.nu; col++) 
            num[col] = 0;
        for (t = 1; t <= M.tu; t++) 
            ++num[M.data[t].j];
        cpot[1] = 1;
        for (int i = 2; i <= M.nu; i++) 
            cpot[i] = cpot[i - 1] + num[i - 1]; //   求出每一列中非零元素在三元组中出现的位置
        for (p = 1; p <= M.tu; p++) {
            int col = M.data[p].j;
            q = cpot[col];
            T.data[q].i = col;
            T.data[q].j = M.data[p].i;
            T.data[q].e = M.data[p].e;
            ++cpot[col];
        }
    }
    // matrix = T;
    cout << "输入矩阵的转置矩阵为: " << endl;
    OutputRLSMatrix(T);
}//TransposeSMatrix

// void TransposeSMatrix(TSMatrix M, TSMatrix &T){
//     // TSMatrix matrix;
//     int num[MAXROW + 1];
//     int cpot[MAXROW + 1]; //   构建辅助数组
//     int q, p, t;
//     T.tu = M.tu;
//     T.mu = M.nu;
//     T.nu = M.mu;
//     if (T.tu) {
//         for (int col = 1; col <= M.nu; col++) 
//             num[col] = 0;
//         for (t = 1; t <= M.tu; t++) 
//             ++num[M.data[t].j];
//         cpot[1] = 1;
//         for (int i = 2; i <= M.nu; i++) 
//             cpot[i] = cpot[i - 1] + num[i - 1]; //   求出每一列中非零元素在三元组中出现的位置
//         for (p = 1; p <= M.tu; p++) {
//             int col = M.data[p].j;
//             q = cpot[col];
//             T.data[q].i = col;
//             T.data[q].j = M.data[p].i;
//             T.data[q].e = M.data[p].e;
//             ++cpot[col];
//         }
//     }
//     // matrix = T;
//     cout << "输入矩阵的转置矩阵为: " << endl;
//     OutputTSMatrix(T);
// }//TransposeSMatrix
