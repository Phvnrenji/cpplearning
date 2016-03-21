#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;
typedef int DataType;
const int ArSize = 10;

typedef struct Node {
	DataType data;
	struct Node *next;
}SLNode;

SLNode *create();
void List(SLNode *head);
//void sequencer(SLNode **head, SLNode *end);
void sequen_one(SLNode *head, int residue);
void sequen_two(SLNode *head, int size);


int main() {
	SLNode *linlist;
	SLNode *linlist_s;
	//	int length;
	//	int series[ArSize];
	//	length = rand();

	linlist = create();
	cout << "=================================\n" << "创建单链表：\n";
	List(linlist);
	cout << "快速排序：\n";
    clock_t q1_start_time=clock();
	sequen_one(linlist, ArSize);
    clock_t q1_end_time=clock();
//	sequencer(&linlist, NULL);
	List(linlist);
    cout << "排序用时: " << static_cast<double>(q1_end_time-q1_start_time)/CLOCKS_PER_SEC*1000 << "ms" << endl;//输出运行时间
	cout << "=================================\n" << "创建单链表：\n";
	linlist_s = create();
	List(linlist_s);
	cout << "冒泡排序：\n";
	clock_t q2_start_time=clock();
    sequen_two(linlist_s, ArSize);
    clock_t q2_end_time=clock();
    
	List(linlist_s);
    cout << "排序用时: "<< static_cast<double>(q2_end_time-q2_start_time)/CLOCKS_PER_SEC*1000 << "ms" << endl;//输出运行时间
    cout << "=================================\n";
//	system("pause");
	return 0;
}

//创建单链表
SLNode *create() {
	SLNode *head, *p, *s;
	int x;
	int length;
	length = ArSize;
    
    /*malloc()函数向系统申请分配一个节点*/
	// head = (SLNode*)malloc(sizeof(Node));
	head = new SLNode;
   
    head->data = 0;
	head->next = NULL;
	p = head;
//	cout << "生成链表：" << endl;
	for (int i = 0; i < length; ++i) {

		x = rand() % 100 + 1;
		// s = (SLNode*)malloc(sizeof(Node));
        s = new SLNode;
		s->data = x;
//		cout << s->data << " ";
		p->next = s;
		p = s;
	}
	//	head = head->next;
	//	head->data = length;
	p->next = NULL;
	//	cout << "头节点：" << head->data << endl;
	return (head);
}

//输出单链表
void List(SLNode *head)
{
	SLNode *p = head;
	int size = 1;
//	cout << "生成链表：\n";
	while (p->next != NULL) {
		p = p->next;
		cout << p->data << " ";
		++size;
	}
	cout << endl;
//	cout << "链表长度：" << size << endl;
}

/****************************************
**函数名：sequen_one
**描述：单链表快速排序
**输入：SLNode * head, int residue
**输出：SLNode * linlist
**返回值：void
**作者：Dvnean
**时间：2016/3/16/14:30
**修改者：----------
**修改时间：----------
**版本号：v1.0
****************************************/
void sequen_one(SLNode * head, int residue)
{
	SLNode * head_s;
	SLNode *povit, *shift, *current;	//基准结点，右移结点和参照结点
	int left_count = 0, right_count = 0;	//左右链表计数
	head_s = head;
	povit = head_s->next;
	shift = povit->next;
	current = povit;
	int povit_value = povit->data;
	for (int i = 1; i < residue; ++i) {		
		if (shift->data <= povit_value) {	//右移结点值小等于基准值，将该结点移动到头节点的下一个结点
			current->next = shift->next;
			shift->next = head_s->next;
			head_s->next = shift;
			left_count++;
			shift = current->next;
		}
		else {								//右移结点大于基准值，右移结点和参照结点右移
			current = shift;
			shift = shift->next;
			right_count++;
		}
	}

	//递归
	if (left_count > 1) {					
		sequen_one(head_s, left_count);
	}
	if (right_count > 1) {
		sequen_one(povit, right_count);
	}

}


/****************************************
**函数名：sequen_two
**描述：单链表冒泡排序
**输入：SLNode *head, int size
**输出：linlist_s
**返回值：void
**作者：Dvnean
**时间：2016/3/16/16:43
**修改者：----------
**修改时间：----------
**版本号：v1.0
****************************************/
void sequen_two(SLNode *head, int size) {
	SLNode *shift, *min_pos, *current, *prev;
	current = min_pos = head->next;
	shift = min_pos->next;
	prev = head;
	for (int i = 1; i < size; ++i ) {
		
		if (min_pos->data > shift->data) {
			min_pos = shift;
			prev = current;
		}
		shift = shift->next;
		current = current->next;
	}
	prev->next = min_pos->next;
	min_pos->next = head->next;
	head->next = min_pos;

	if (min_pos->next != NULL) {
		sequen_two(min_pos, size-1);
	}
}
