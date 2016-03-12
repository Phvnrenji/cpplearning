#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct Node {
	int data;
	struct Node *next;
}SLNode;
const int ArSize = 10;

SLNode *create();
int ListLength(SLNode *head);

int main() {
	SLNode *linlist;
	int size = 0;
//	int length;
//	int series[ArSize];
//	length = rand();

	linlist = create();
	size = ListLength(linlist);
	cout << "size of linlist is: " << size << endl;
	// system("pause");
	return 0;
}

SLNode *create() {
	SLNode *head, *p, *s;
	int x;
	int length;
	length = 100;
	head = (SLNode*)malloc(sizeof(Node));//malloc()函数向系统申请分配一个节点
	head->next = NULL;
	p = head;
	cout << "生成链表：" << endl;
	for (int i = 0; i < length; ++i) {
		/*		cout << "\nPlease input the data: ";
				cin >> x;

				if (x != 1) {
					s = (SLNode*)malloc(sizeof(Node));
					s->data = x;
					cout << s->data;
					p->next = s;
					p = s;
				}
				else
					cycle = 0;
			}
			head = head->next;
			p->next = NULL;
			cout << "\n	yyy " << head->data << endl;
		*/
		x = rand();
		s = (SLNode*)malloc(sizeof(Node));
		s->data = x;
		cout << s->data << endl;
		p->next = s;
		p = s;
	}
//	head = head->next;
//	head->data = length;
	p->next = NULL;
//	cout << "头节点：" << head->data << endl;
	return (head);
}

int ListLength(SLNode *head)
{
	SLNode *p = head;
	int size = 1;
	while (p->next != NULL) {
		p = p->next;
		++size;
	}
	return size;
}