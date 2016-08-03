//stock10.h -- Stock class declaration with constructors, destructor added
//version 10

#ifndef STOCK00_H_
#define STOCK00_H_

#include <String>

class Stock{
    private:
        std::string company;
        long shares;
        double share_val;
        double total_val;
        void set_tot() { total_val = shares * share_val; }
    public:
        // void acquire(const std::string & co, long n, double pr);
    //two constructors
        Stock();    //default constructor
        Stock(const std::string & co, long n = 0, double pr = 0.0);
        ~Stock();   //析构函数
        void buy(long num, double price);
        void sell(long num, double price);
        void update(double price);
        void show();
        
};

#endif