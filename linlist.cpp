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
int ListLength(SLNode *head);
void sequencer(SLNode **head, SLNode *end);

int main() {
	SLNode *linlist;
	int size = 0;
//	int length;
//	int series[ArSize];
//	length = rand();

	linlist = create();
	size = ListLength(linlist);
	cout << endl << "size of linlist is: " << size << endl;
	sequencer(&linlist, NULL);
    // system("pause");
	return 0;
}

SLNode *create() {
	SLNode *head, *p, *s;
	int x;
	int length;
	length = ArSize;
	head = (SLNode*)malloc(sizeof(Node));//malloc()函数向系统申请分配一个节点
	head->next = NULL;
	p = head;
	cout << "生成链表：" << endl;
	for (int i = 0; i < length; ++i) {
		
		x = rand() % 100 + 1;
		s = (SLNode*)malloc(sizeof(Node));
		s->data = x;
		cout << s->data << " ";
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
void sequencer(SLNode **head, SLNode *end){
    SLNode *right;
    SLNode **left_shift, **right_shift;
    SLNode *refer, *prev;
    int count, left_count = 0, right_count = 0;
    if(*head == end)
        return;
    do{
        refer = *head;
        left_shift = head;
        right_shift = &right;
        for(prev = (*head)->next;; prev != end; prev = prev->next){
            if(prev->data < refer->data){
                ++left_count;
                *left_shift = prev;
                left_shift = &(prev->next);
            }
            else{
                ++right_count;
                *right_shift = prev;
                right_shift = &(prev -> next);
            }
        }
        
        *right_shift = end;
        *left_shift = refer;
        refer->next = right;
        
        if(left_shift > right_shift){
            sequencer(&(refer->next), end);
            end = refer;
            count = left_count;
        }
        else{
            sequencer(head, refer);
            head = &(refer->next);
            count = right_count;
        }
    }while(count > 1);
}