/**
 * @file 9_dynamic_type.cpp
 * @brief C++ dynamic type test code
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-24
 */
#include <iostream>
using namespace std;

class Base1
{
    int x;
    int y;

public:
    virtual ~Base1() = default;

    virtual void process() { cout << "<====== Base1::process() ======>" << endl; }
};

class Sub1 : public Base1
{ //继承
public:
    int value;

    void process() override
    {
        cout << "<====== Sub1::process() ======>" << endl;
        Base1::process();
    }

    void func() { cout << __FUNCTION__ << " called" << endl; }
};

void process(Base1 * pb) //多态基类
{
    const type_info & tf = typeid(*pb);
    cout << "Base1* pb type name " << tf.name() << endl;
    if (tf == typeid(Sub1))
    {
        cout << "pb是一个Sub1*" << endl;
    }
    else if (tf == typeid(Base1))
    {
        cout << "pb是一个Base1*" << endl;
    }

    pb->process(); //多态辨析 dynamic dispatch

    Sub1 * ps = dynamic_cast<Sub1 *>(pb); //多态转型
    // Sub1* p2=(Sub1*)pb; C-转型

    if (ps != nullptr)
    {
        cout << "pb是一个Sub1*" << endl;
        ps->func(); // 非多态辨析
    }
    else
    {
        cout << "pb不是一个Sub1*" << endl;
    }
}

void process(Base1 & rhs)
{
    cout << "const Base1& rhs" << endl;
    rhs.process();
}

int main()
{
    Base1 * p1 = new Base1();
    Base1 * p2 = new Sub1();

    process(p1);
    process(p2);
    process(*p1);
    process(*p2);

    Base1 & b1 = *p2;
    Sub1 & s2  = dynamic_cast<Sub1 &>(b1);
    s2.value++;

    Base1 * p3 = new Sub1();

    //全局唯一、只读
    const type_info & t1 = typeid(*p1);
    const type_info & t2 = typeid(*p2);
    const type_info & t3 = typeid(*p3);

    cout << "t1 name is " << t1.name() << endl;
    cout << "t2 name is " << t2.name() << endl;
    cout << "t3 name is " << t3.name() << endl;
    if (t1 == t2)
    {
        cout << "t1 == t2" << endl;
    }

    if (t2 == t3)
    {
        cout << "t2 == t3" << endl;
    }

    if (t1 == t3)
    {
        cout << "t1 == t3" << endl;
    }

    if (t1.__is_pointer_p())
    {
        cout << "t1 is pointer" << endl;
    }
    else if (t1.__is_function_p())
    {
        cout << "t1 is function pointer" << endl;
    }
    else
    {
        cout << "t1 is not pointer" << endl;
    }

    delete p1;
    delete p2;
}
