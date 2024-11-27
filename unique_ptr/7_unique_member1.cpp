/**
 * @file 7_unique_member1.cpp
 * @brief unique_ptr的成员变量的使用方法，以及unique_ptr的移动语义的使用方法, delete copy ctor and copy assignment, only move type
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-25
 */
#include <iostream>
#include <memory>

using namespace std;

class Widget
{
public:
    Widget() { cout << "ctor" << endl; }
    ~Widget() { cout << "dtor" << endl; }

    Widget(const Widget & rhs) { cout << "copy ctor" << endl; }
    Widget(Widget && rhs) { cout << "move ctor" << endl; }

    Widget & operator=(Widget && rhs)
    {
        cout << "move assignment" << endl;
        return *this;
    }
    Widget & operator=(const Widget & rhs)
    {
        cout << "copy assignment" << endl;
        return *this;
    }
};

struct MyClass
{
    // Widget* w;
    std::unique_ptr<Widget> m_p; // move-only type
};

/*
// 等价于下面的代码
struct MyClass {

    std::unique_ptr<Widget> m_p;

    MyClass() noexcept = default;
    ~MyClass() noexcept = default;
    MyClass(MyClass && ) noexcept = default;
    MyClass & operator=( MyClass &&) noexcept = default;

    MyClass(const MyClass &)  = delete;
    MyClass & operator=(const MyClass &)  = delete;

};*/

int main()
{
    MyClass c1;
    c1.m_p = make_unique<Widget>();

    // MyClass c2=c1; // Error
    MyClass c2 = std::move(c1);

    cout << std::boolalpha;
    cout << (c1.m_p == nullptr) << endl;
    cout << (c2.m_p == nullptr) << endl;

    cout << "-----" << endl;
    {
        MyClass c3;
        c3.m_p = make_unique<Widget>();
        // c3=c2;   // Error
        c3 = std::move(c2);
        cout << (c2.m_p == nullptr) << endl;
        cout << (c3.m_p == nullptr) << endl;
    }

    cout << "-----" << endl;
    cout << std::is_move_constructible<MyClass>::value << endl;    // true
    cout << std::is_move_assignable<MyClass>::value << endl;       // true
    cout << std::is_copy_constructible<MyClass>::value << endl;    // false
    cout << std::is_copy_assignable<MyClass>::value << endl;       // false
    cout << std::is_default_constructible<MyClass>::value << endl; // true
    cout << std::is_destructible<MyClass>::value << endl;          // true
}
