/**
 * @file 10_crtp_interface.cpp
 * @brief CRTP模式深入: Curiously Recurring Template Pattern, 奇异递归模板模式, Non-virtual interface(NVI)模式
 *        通过模板参数T包含了子类编译时信息，实现了编译时多态, 通过基类指针转型为子类T的指针
 *        它允许一个类将自己作为模板参数传递给基类，从而实现静态多态性和编译时多态性
 * @author Albert
 * @version 1.0.0
 * @date 2025-03-29
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
    ~Base() { cout << "~Base()" << endl; }

public:
    Base() { cout << "Base()" << endl; }

    void process()
    {
        sub()->process_imp(); // 编译时分发
    }
    // 如果子类不实现，就使用基类默认实现的函数，类似虚函数
    void process_imp() { cout << "Base::process()" << endl; }

    // 将基类指针转型为子类T的指针
    T * sub()
    {
        // cout << "Base<T>* ---> T* converted Base<Sub>* ---> Sub*" << endl;
        return static_cast<T *>(this);
    }
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

    // void process_imp() { cout << "Sub2::process()" << endl; }
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
        unique_ptr<Sub1> ps1 = make_unique<Sub1>();
        ps1->process(); // process(ps1)
        invoke(ps1.get());
        cout << "data = " << ps1->sub()->data << endl;
        cout << ps1->sub()->p << " shared_ptr<int> p value = " << *(ps1->sub()->p) << endl;
    }

    {
        cout << "----------------" << endl;
        unique_ptr<Sub2> ps2 = make_unique<Sub2>();
        ps2->process();
        invoke(ps2.get());
    }

    {
        cout << "----------------" << endl;
        unique_ptr<Sub3> ps3 = make_unique<Sub3>();
        ps3->process();
        invoke(ps3.get());
    }

    {
        cout << "----------------" << endl;
        unique_ptr<Sub1> ps1 = make_unique<Sub1>();
        ps1->process();
        invoke(ps1.get());
        cout << "data = " << ps1->data << endl;
    }

    {
        cout << "----------------" << endl;
        Sub1 s1;
        s1.process();
        invoke(&s1);
    }
}
