//stack.h -- class definition for the stack ADT
//ADT:abstract data type 抽象数据类型
#ifndef STACK_H_
#define STACK_H_

typedef unsigned long Item;

class Stack{
private:
    enum {MAX = 10};        //constant specific to class
    Item items[MAX];        //holds stack items
    int top;                //index for top item
public:
    Stack();
    bool isempty() const;
    bool isfull() const;
    //push() returns false if stack laready is full, true otherwise
    bool push(const Item & item);
    //pop() returns false if stack already is empty, ture otherwise
    bool pop(Item & item);
};

#endif
