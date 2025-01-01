/**
 * @file 2_tuple.cpp
 * @brief std::tuple 是一个模板类，用于存储一组任意数量的任意类型的值，它是一个简单的数据结构，包含多个公有成员变量。
 *        std::tuple 支持拷贝、移动、析构，实际是对成员的委托调用
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

tuple<int, string, double> get_book(int id)
{
    if (id == 100)
        return std::make_tuple(100, "C++ Programming Language", 100.5);
    if (id == 200)
        return std::make_tuple(200, "Effective Modern C++", 80.00);
    if (id == 300)
        return std::make_tuple(300, "Design Patterns", 45.5);

    return std::make_tuple(0, "", 0.0);
}

int main()
{
    tuple book1 = get_book(100);
    cout << std::get<0>(book1) << ", " << std::get<1>(book1) << std::get<2>(book1) << '\n';

    int id1;
    string name1;
    double price1;

    // 引用包装器: std::tie 是一个标准库函数模板，用于创建一个 std::tuple 对象的引用包装器
    std::tie(id1, name1, std::ignore) = get_book(200);
    cout << id1 << ", " << name1 << '\n';

    // C++17 结构化绑定
    auto [id2, name2, price2] = get_book(300);
    cout << id2 << ", " << name2 << ", " << price2 << '\n';

    tuple<int, Widget> t{ 100, getWidget() };
}
