/**
 * @file 1_pair.cpp
 * @brief std::pair 是一个模板类，用于存储一对任何类型的值，它是一个简单的数据结构，包含两个公有成员变量 first 和 second。
 *        std::pair 支持拷贝、移动、析构，实际是对成员 first and second 的委托调用
 *            拷贝构造和拷贝赋值：当你拷贝一个 std::pair 对象时，会调用 first 和 second 成员的拷贝构造函数或拷贝赋值运算符。
 *            移动构造和移动赋值：当你移动一个 std::pair 对象时，会调用 first 和 second 成员的移动构造函数或移动赋值运算符。
 *            析构：当一个 std::pair 对象被销毁时，会调用 first 和 second 成员的析构函数。
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-26
 */
#include <complex>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>

using namespace std;

class Widget
{
public:
    int m_data;

    Widget(int data) : m_data(data) { cout << "ctor" << endl; }
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

Widget getWidget()
{
    Widget w(100);
    return w;
}

int main()
{
    std::pair<int, double> p1{ 42, 3.1415 };
    cout << p1.first << "," << p1.second << endl;

    // C++17 之前，支持模版函数自动推导
    auto p2 = make_pair(42, 3.1415); // std::pair<int, double> p2{42, 3.1415};

    // C++17 及之后，支持构造函数参数类型推导
    std::pair p3{ 42, 3.1415 };

    // int convert to char
    std::pair<char, int> p4{ p3 };
    cout << p4.first << "," << p4.second << endl;

    pair<string, Widget> p5{ "hello"s, getWidget() };

    pair p6 = p5;
    pair p7 = std::move(p6);
}
