#include <iostream>
#include <stdlib.h>
using namespace std;
typedef int DataType;

typedef struct Node {
	DataType data;
	struct Node *next;
}SLNode;
const int ArSize = 10;

SLNode *create();
void List(SLNode *head);
//void sequencer(SLNode **head, SLNode *end);
void sequen_one(SLNode *head, int residue);

int main() {
	SLNode *linlist;
	int size = 0;
	//	int length;
	//	int series[ArSize];
	//	length = rand();

	linlist = create();
    cout << "生成链表：" << endl;
	List(linlist);
	sequen_one(linlist, ArSize);
//	sequencer(&linlist, NULL);
    cout << "链表排序：" << endl;
	List(linlist);
//	 system("pause");
	return 0;
}

SLNode *create() {
	SLNode *head, *p, *s;
	int x;
	int length;
	length = ArSize;
	head = (SLNode*)malloc(sizeof(Node));//malloc()函数向系统申请分配一个节点
	head->data = 0;
	head->next = NULL;
	p = head;
//	cout << "生成链表：" << endl;
	for (int i = 0; i < length; ++i) {

		x = rand() % 100 + 1;
		s = (SLNode*)malloc(sizeof(Node));
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
**函数名：
**输入：
**输出：
**返回值：
**作者：
**时间：
**修改者：
**修改时间：
**版本号：
****************************************/
/*
void sequencer(SLNode **head, SLNode *end) {
	SLNode *right;
	SLNode **left_shift, **right_shift;
	SLNode *refer, *prev;
	int count, left_count = 0, right_count = 0;
	if (*head == end)
		return;
	do {
		refer = *head;
		left_shift = head;
		right_shift = &right;
		for (prev = (*head)->next; prev != end; prev = prev->next) {
			if (prev->data < refer->data) {
				++left_count;
				*left_shift = prev;
				left_shift = &(prev->next);
			}
			else {
				++right_count;
				*right_shift = prev;
				right_shift = &(prev->next);
			}
		}

		*right_shift = end;
		*left_shift = refer;
		refer->next = right;

		if (left_shift > right_shift) {
			sequencer(&(refer->next), end);
			end = refer;
			count = left_count;
		}
		else {
			sequencer(head, refer);
			head = &(refer->next);
			count = right_count;
		}
	} while (count > 1);
	
}
*/