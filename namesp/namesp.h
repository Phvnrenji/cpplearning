// namesp.h
#include <string>
// creat the pers and debts namespaces
namespace pers{
    struct Person{
        std::string fname;
        std::string lname;
    };
    void getPerson(Person &);
    void showPerson(const Person &);
}//包含Person结构的定义和两个函数原型----一个函数用人名填充结构，另一个函数显示结构的内容

namespace debts{
    using namespace pers;
    struct Debt{
        Person name;
        double amount;
    };
    //function prototypes
    void getDebt(Debt &);
    void showDebt(const Debt &);
    double sumDebts(const Debt ar[], int n);
}//定义了一个结构，该结构用来存储人名和金额。
 //该结构使用了Person结构，因此，debts名称空间使用一条using编译指令，让pers中的名称在debts名称空间可用
