#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
const int MAXSIZE = 100; // 定义非零元素的对多个数
const int MAXROW = 10; // 定义数组的行数的最大值

typedef struct {
    int i, j;
    int e;
} Triple; // 定义三元组的元素

typedef struct {
    Triple data[MAXSIZE + 1];
    int mu, nu, tu;
} TSMatrix; // 定义普通三元组对象

typedef struct {
    Triple data[MAXSIZE + 2];
    int rpos[MAXROW + 1];
    int mu, nu, tu;
} RLSMatrix; // 定义带链接信息的三元组对象

typedef struct OLNode { // 定义十字链表元素
    int i, j;
    int e;
    struct OLNode *right, *down; //  该非零元所在行表和列表的后继元素
} OLNode, *OLink; // 定义十字链表元素

typedef struct { //   定义十字链表对象结构体
    OLink *rhead, *chead;
    int mu, nu, tu; //   系数矩阵的行数，列数，和非零元素个数
} CrossList; //   定义十字链表对象结构体

template <class P>
bool InPutTSMatrix(P & T, int y) { //输入矩阵，按三元组格式输入
    cout << "输入矩阵的行，列和非零元素个数:" << endl;
    cin >> T.mu >> T.nu >> T.tu;
    cout << "请输出非零元素的位置和值:" << endl;
    int k = 1;
    for (; k <= T.tu; k++)
        cin >> T.data[k].i >> T.data[k].j >> T.data[k].e;
    return true;
}

template <class P>
bool OutPutSMatrix(P T) {
    int m, n, k = 1;
    for (m = 0; m < T.mu; m++) {
        for (n = 0; n < T.nu; n++) {
            if ((T.data[k].i - 1) == m && (T.data[k].j - 1) == n) {
                cout.width(4);
                cout << T.data[k++].e;
            } else {
                cout.width(4);
                cout << "0";
            }
        }
        cout << endl;
    }
    return true;
}// 输出矩阵，按标准格式输出

bool TransposeSMatrix() {
    TSMatrix M, T; //定义预转置的矩阵
    InPutTSMatrix(M, 0); //输入矩阵
    int num[MAXROW + 1];
    int cpot[MAXROW + 1]; //   构建辅助数组
    int q, p, t;
    T.tu = M.tu;
    T.mu = M.nu;
    T.nu = M.mu;
    if (T.tu) {
        for (int col = 1; col <= M.nu; col++) num[col] = 0;
        for (t = 1; t <= M.tu; t++) ++num[M.data[t].j];
        cpot[1] = 1;
        for (int i = 2; i <= M.nu; i++) cpot[i] = cpot[i - 1] + num[i - 1]; //   求出每一列中非零元素在三元组中出现的位置
        for (p = 1; p <= M.tu; p++) {
            int col = M.data[p].j;
            q = cpot[col];
            T.data[q].i = col;
            T.data[q].j = M.data[p].i;
            T.data[q].e = M.data[p].e;
            ++cpot[col];
        }
    }
    cout << "输入矩阵的转置矩阵为" << endl;
    OutPutSMatrix(T);
    return true;
}// 求矩阵的转置矩阵

bool Count(RLSMatrix &T) {
    int num[MAXROW + 1];
    for (int col = 1; col <= T.mu; col++) num[col] = 0;
    for (int col = 1; col <= T.tu; col++) ++num[T.data[col].i];
    T.rpos[1] = 1;
    for (int i = 2; i <= T.mu; i++) T.rpos[i] = T.rpos[i - 1] + num[i - 1]; // 求取每一行中非零元素在三元组中出现的位置

    return true;
}

bool MultSMatrix() {
    RLSMatrix M, N, Q; // 构建三个带“链接信息”的三元组表示的数组
    InPutTSMatrix(M, 1); //  用普通三元组形式输入数组
    InPutTSMatrix(N, 1);
    Count(M);
    Count(N);
    cout << "输入的两矩阵的乘矩阵为：" << endl;
    if (M.nu != N.mu) return false;
    Q.mu = M.mu;
    Q.nu = N.nu;
    Q.tu = 0; //     Q初始化
    int ctemp[MAXROW + 1]; //    辅助数组
    int arow, tp, p, brow, t, q, ccol;
    if (M.tu * N.tu) { //  Q是非零矩阵
        for (arow = 1; arow <= M.mu; arow++) {
            ///memset(ctemp,0,N.nu);
            for (int x = 1; x <= N.nu; x++) // 当前行各元素累加器清零
                ctemp[x] = 0;
            Q.rpos[arow] = Q.tu + 1; //  当前行的首个非零元素在三元组中的位置为此行前所有非零元素+1
            if (arow < M.mu) 
                tp = M.rpos[arow + 1];
            else 
                tp = M.tu + 1;
            for (p = M.rpos[arow]; p < tp; p++) { //   对当前行每个非零元素进行操作
                brow = M.data[p].j; //  在N中找到i值也操作元素的j值相等的行
                if (brow < N.mu) 
                    t = N.rpos[brow + 1];
                else 
                    t = N.tu + 1;
                for (q = N.rpos[brow]; q < t; q++) { //  对找出的行当每个非零元素进行操作

                    ccol = N.data[q].j;
                    ctemp[ccol] += M.data[p].e * N.data[q].e; //    将乘得到对应值放在相应的元素累加器里面
                }
            }
            for (ccol = 1; ccol <= Q.nu; ccol++) //   对已经求出的累加器中的值压缩到Q中
                if (ctemp[ccol]) {
                    if (++Q.tu > MAXSIZE) return false;
                    Q.data[Q.tu].e = ctemp[ccol];
                    Q.data[Q.tu].i = arow;
                    Q.data[Q.tu].j = ccol;
                }
        }
    }
    
    OutPutSMatrix(Q);
    return true;
}// 两个矩阵相乘

bool CreateSMatrix_OL(CrossList & M) {
    int x, y, m;

    cout << "请输入矩阵的行，列，及非零元素个数" << endl;
    cin >> M.mu >> M.nu >> M.tu;
    if (!(M.rhead = (OLink*) malloc((M.mu + 1) * sizeof (OLink)))) exit(0);
    if (!(M.chead = (OLink*) malloc((M.nu + 1) * sizeof (OLink)))) exit(0);
    for (x = 0; x <= M.mu; x++)
        M.rhead[x] = NULL; // 初始化各行，列头指针，分别为NULL
    for (x = 0; x <= M.nu; x++)
        M.chead[x] = NULL;
    cout << "请按三元组的格式输入数组：" << endl;
    for (int i = 1; i <= M.tu; i++) {
        cin >> x >> y >> m; //  按任意顺序输入非零元，（普通三元组形式输入）
        OLink p, q;
        if (!(p = (OLink) malloc(sizeof (OLNode)))) exit(0); // 开辟新节点，用来存储输入的新元素
        p->i = x;
        p->j = y;
        p->e = m;
        if (M.rhead[x] == NULL || M.rhead[x]->j > y) {
            p->right = M.rhead[x];
            M.rhead[x] = p;
        } else {
            for (q = M.rhead[x]; (q->right) && (q->right->j < y); q = q->right); //   查找节点在行表中的插入位置
            p->right = q->right;
            q->right = p; //   完成行插入
        }
        if (M.chead[y] == NULL || M.chead[y]->i > x) {
            p->down = M.chead[y];
            M.chead[y] = p;
        } 
        else {
            for (q = M.chead[y]; (q->down) && (q->down->i < x); q = q->down); //       查找节点在列表中的插入位置
            p->down = q->down;
            q->down = p; //  完成列插入

        }
    }
    return true;
}//   创建十字链表

bool OutPutSMatrix_OL(CrossList T) { //  输出十字链表，用普通数组形式输出
    for (int i = 1; i <= T.mu; i++) {
        OLink p = T.rhead[i];
        for (int j = 1; j <= T.nu; j++) {
            if ((p) && (j == p->j)) {
                cout << setw(3) << p->e;
                p = p->right;
            } else
                cout << setw(3) << "0";
        }
        cout << endl;
    }
    return true;
}//输出十字链表

bool AddSMatrix() {
    CrossList M, N; //  创建两个十字链表对象，并初始化
    CreateSMatrix_OL(M);
    CreateSMatrix_OL(N);
    cout << "输入的两矩阵的和矩阵为：" << endl;
    OLink pa, pb, pre, hl[MAXROW + 1]; //定义辅助指针，pa，pb分别为M,N当前比较的元素，pre为pa的前驱元素
    for (int x = 1; x <= M.nu; x++) hl[x] = M.chead[x];
    for (int k = 1; k <= M.mu; k++) { // 对M的每一行进行操作
        pa = M.rhead[k];
        pb = N.rhead[k];
        pre = NULL;
        while (pb) { // 把N中此行的每个元素取出，
            OLink p;
            if (!(p = (OLink) malloc(sizeof (OLNode)))) exit(0); //  开辟新节点，存储N中取出的元素
            p->e = pb->e;
            p->i = pb->i;
            p->j = pb->j;
            if (NULL == pa || pa->j > pb->j) { //  当M此行已经检查完或者pb因该放在pa前面

                if (NULL == pre)
                    M.rhead[p->i] = p;
                else
                    pre->right = p;
                p->right = pa;
                pre = p;
                if (NULL == M.chead[p->j]) { // 进行列插入
                    M.chead[p->j] = p;
                    p->down = NULL;
                } else {
                    p->down = hl[p->j]->down;
                    hl[p->j]->down = p;
                }
                hl[p->j] = p;
                pb = pb->right;
            } else
                if ((NULL != pa) && pa->j < pb->j) { //  如果此时的pb元素因该放在pa后面，则取以后的pa再来比较
                pre = pa;
                pa = pa->right;
            } else
                if (pa->j == pb->j) { // 如果pa，pb位于同一个位置上，则将值相加
                pa->e += pb->e;
                if (!pa->e) { // 如果相加后的和为0，则删除此节点，同时改变此元素坐在行，列的前驱元素的相应值
                    if (NULL == pre) // 修改行前驱元素值
                        M.rhead[pa->i] = pa->right;
                    else
                        pre->right = pa->right;
                    p = pa;
                    pa = pa->right;
                    if (M.chead[p->j] == p) M.chead[p->j] = hl[p->j] = p->down; // 修改列前驱元素值
                    else
                        hl[p->j]->down = p->down;
                    free(p);
                    pb = pb->right;
                } else {
                    pa = pa->right;
                    pb = pb->right;
                }
            }

        }
    }
    OutPutSMatrix_OL(M);
    return true;
}//矩阵的加法

int main() {
    cout.fill('*');
    cout << setw(80) << '*';
    cout.fill(' ');
    // system("color 0C");
    cout << setw(50) << "***欢迎使用矩阵运算程序***" << endl; //输出头菜单
    cout.fill('*');
    cout << setw(80) << '*';
    cout.fill(' ');
    cout << "                        请选择要进行的操作：" << endl;
    cout << "                        1:矩阵的转置。" << endl;
    cout << "                        2:矩阵的加法。" << endl;
    cout << "                        3:矩阵的乘法。" << endl;
    cout << "                        4:退出程序。" << endl;
    cout << "请输入您的选择： ";
    // printf("请输入您的选择：");
    char c ;
    cin >> c;
    if (c == '1')
        TransposeSMatrix(); //调用矩阵转置函数
    else
        if (c == '2')
        AddSMatrix(); //调用矩阵相加函数
    else
        if (c == '3')
        MultSMatrix(); //调用矩阵相乘函数
    else
        exit(0); //退出
    return 0;
}