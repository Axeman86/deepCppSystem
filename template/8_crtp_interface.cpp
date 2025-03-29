/**
 * @file 8_crtp_interface.cpp
 * @brief CRTP模式深入: Curiously Recurring Template Pattern, 奇异递归模板模式, Non-virtual interface(NVI)模式
 *        通过模板参数T包含了子类编译时信息，实现了编译时多态, 通过基类指针转型为子类T的指针
 *        它允许一个类将自己作为模板参数传递给基类，从而实现静态多态性和编译时多态性
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-21
 */
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// 基类参数T包含了子类编译时信息
template <typename T>
class Base
{
protected:
    ~Base()
    {
        // 子类析构函数会调用自己的父类析构函数，所以这里不需要delete，不然会重复delete进入死循环
        // delete sub(); // static_cast<T*>(this);
        cout << "~Base()" << endl;
    }

public:
    Base() { cout << "Base()" << endl; }

    void process()
    {
        sub()->process_imp(); // 编译时分发
    }
    // 如果不实现，类似纯虚函数
    void process_imp() { cout << "Base::process()" << endl; }

    // 将基类指针转型为子类T的指针
    // ==> shared_from_this() return shared_ptr<T>
    T * sub() { return static_cast<T *>(this); } //  Base<T>* ---> T* converted Base<Sub1>* ---> Sub1*

    void destroy()
    {
        delete sub(); // static_cast<T*>(this);
    }

    // 不能包含子类对象，否则会造成无限递归
    // T* sub;
};

class Sub1 : public Base<Sub1>
{
public:
    int data = 99;
    shared_ptr<int> p;
    Sub1()
    {
        cout << "Sub1()" << endl;
        p = make_shared<int>(10);
        cout << "shared_ptr<int> p value = " << *p << endl;
    }
    ~Sub1() { cout << "~Sub1()" << endl; }

    void process_imp() { cout << "Sub1::process()" << endl; }
};

class Sub2 : public Base<Sub2>
{
public:
    Sub2() { cout << "Sub2()" << endl; }
    ~Sub2() { cout << "~Sub2()" << endl; }

    void process_imp() { cout << "Sub2::process()" << endl; }
};

class Sub3 : public Base<Sub3>
{
public:
    Sub3() { cout << "Sub3()" << endl; }
    ~Sub3() { cout << "~Sub3()" << endl; }

    void process_imp() { cout << "Sub3::process()" << endl; }
};

template <typename T>
void invoke(Base<T> * pb)
{
    pb->process();
}

int main()
{
    {
        Sub1 * ps1 = new Sub1();
        ps1->process(); // process(ps1)

        invoke(ps1);
        cout << "data = " << ps1->sub()->data << endl;
        cout << ps1->sub()->p << " shared_ptr<int> p value = " << *(ps1->sub()->p) << endl;

        // delete ps1; // ERROR: 会调用~Base()，然后调用~Sub1()，然后调用~Base()，然后调用~Sub1()，进入死循环
        // delete ps1->sub(); // ERROR: 会调用~Base()，然后调用~Sub1()，然后调用~Base()，然后调用~Sub1()，进入死循环
        ps1->destroy();
    }

    {
        cout << "----------------" << endl;
        Sub2 * ps2 = new Sub2();
        ps2->process();
        invoke(ps2);
        ps2->destroy();
    }

    {
        cout << "----------------" << endl;
        Sub3 * ps3 = new Sub3();
        ps3->process();
        invoke(ps3);
        ps3->destroy();
    }

    {
        cout << "----------------" << endl;
        // Base<Sub2> obj; // ERROR: Sub2()构造函数不能被调用
        Sub2 obj;
    }

    {
        cout << "----Test object memory truncation----" << endl;
        // new Base<Sub1>() 和 new Sub1() 的区别是什么？
        // sizeof(Base<Sub1>)=1Byte 和 sizeof(Sub1)=24Byte, 申请的内存大小不一样
        cout << "sizeof(Base<Sub1>) : " << sizeof(Base<Sub1>) << endl;
        cout << "sizeof(Sub1) : " << sizeof(Sub1) << endl;

        // WARNING: Sub1() constructor 不被调用，只调用了Base() construcotr，因为Base<Sub1>的构造函数没有调用Sub1的构造函数
        Base<Sub1> * psx = new Base<Sub1>();
        psx->process();
        invoke(psx);
        // 访问子类成员变量，会出现段错误; 因为Sub1()构造函数没有被调用，出现了内存被截断的情况，因为根本没有为子类分配内存
        /* cout << "data = " << ps2->sub()->data << endl; */
        /* cout << ps2->sub()->p << " shared_ptr<int> value = " << *(ps2->sub()->p) << endl; */
        psx->destroy();

        // Error: Base<int> * pi = new Sub1();
        /* Base<int> * pi = new Base<int>();
         * pi->process(); */
    }
}
