/**
 * @file 8_unique_member2.cpp
 * @brief unique_ptr 的成员变量的使用：unique_ptr 作为成员变量时，类的拷贝构造函数和拷贝赋值运算符默认会被删除，只能使用移动语义
 *                   如果需要使用拷贝构造函数和拷贝赋值运算符，需要自己实现
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-25
 */
#include <iostream>
#include <memory>

using namespace std;

struct Widget
{
    int m_number;

    Widget(int number = 0) : m_number(number) { cout << "Widget()" << endl; }
    Widget(const Widget & w) : m_number(w.m_number) { cout << "Widget(const Widget& w)" << endl; }

    Widget(Widget && w) : m_number(w.m_number) { cout << "Widget(Widget&& w)" << endl; }
    Widget & operator=(const Widget & w)
    {
        if (this == &w)
            return *this;

        cout << "operator=(const Widget& w)" << endl;
        m_number = w.m_number;
        return *this;
    }
    Widget & operator=(Widget && w)
    {
        if (this == &w)
            return *this;

        cout << "operator=(Widget&& w)" << endl;
        m_number = w.m_number;
        return *this;
    }
    ~Widget() { cout << "~Widget()" << endl; }
};

struct MyClass
{
    // Widget* w;
    std::unique_ptr<Widget> m_p;

    MyClass(int data) : m_p{ make_unique<Widget>(data) } {}

    MyClass(const MyClass & rhs) : m_p(make_unique<Widget>(*rhs.m_p))
    {
        // m_p= unique_ptr<Widget>{ new Widget(*rhs.m_p) };
    }

    MyClass & operator=(const MyClass & rhs)
    {
        if (this == &rhs)
            return *this;

        cout << "operator=(const MyClass& rhs)" << endl;
        MyClass temp(rhs);
        m_p.swap(temp.m_p);
        return *this;
    }

    MyClass(MyClass && rhs) noexcept             = default;
    MyClass & operator=(MyClass && rhs) noexcept = default;
    ~MyClass()                                   = default;
};

int main()
{
    MyClass a(100);

    MyClass b{ a }; // copy ctor

    MyClass c = std::move(b); // copy assignment

    cout << std::boolalpha;
    cout << (a.m_p == nullptr) << endl; // false
    cout << (b.m_p == nullptr) << endl; // true
    cout << (c.m_p == nullptr) << endl; // false
}
