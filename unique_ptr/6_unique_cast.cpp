/**
 * @file 6_unique_cast.cpp
 * @brief unique_ptr的多态性的维持, 可以将派生类的指针赋值给基类的unique_ptr, 但是不能将基类的指针赋值给派生类的unique_ptr
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-25
 */
#include <iostream>
#include <memory>
using namespace std;

class Base
{
public:
    int a;
    virtual void process() { std::cout << "Base.process()" << endl; }

    virtual ~Base() { cout << "~Base()" << endl; }
};

class Sub : public Base
{
public:
    void process() override { std::cout << "Sub.process()" << endl; }

    ~Sub() { cout << "~Sub()" << endl; }
};

int main()
{
    {
        unique_ptr<Base> b1 = std::make_unique<Base>();
        b1->process();

        unique_ptr<Sub> s1 = std::make_unique<Sub>();
        s1->process();

        // Sub* ps=new Sub();
        // Base* pb=ps;
        // pb->process();
        unique_ptr<Base> b2{ std::move(s1) }; // Base* pb= ps;
        b2->process();                        //智能指针维持多态性

        unique_ptr<Base> b3{ new Sub() };
        b3->process();
    }
    cout << "-----" << endl;
    {
        unique_ptr<Base> upb = make_unique<Sub>();

        // unique_ptr<Sub> ups=(unique_ptr<Sub>)std::move(upb); 错误！

        unique_ptr<Sub> ups(dynamic_cast<Sub *>(upb.release())); // Base* --> Sub*
        ups->process();

        // double delete错误！
        //  Base* pb=new Base();
        //  unique_ptr<Base> b1{pb};
        //  unique_ptr<Base> b2{pb};

        //  unique_ptr<Base> b1{new Base()};
        //  unique_ptr<Base> b2{b1.get()};
    }
}
