/**
 * @file 19_ref_functor.cpp
 * @brief std::reference_wrapper 是一个标准库模板类，用于包装引用，使其可以像对象一样进行拷贝、赋值操作
 *        std::ref 和 std::cref 是 std::reference_wrapper 的工厂函数, create a reference_wrapper object from a reference
 * @author Albert
 * @version 1.0
 * @date 2025-01-23
 */
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;

class Widget
{
public:
    int no;
    string name;
    Widget(int _no, const std::string & _name) : no(_no), name(_name) {}

    void print() { cout << no << ": " << name << " " << endl; }
};

void update(Widget & w)
{
    w.no += 1;
    w.name = "[" + w.name + "]";
}

int main()
{
    std::vector<Widget> widgets;

    Widget w1(100, "C++");
    Widget w2(200, "Java");

    update(w1);
    w1.print();

    auto binder1 = bind(&update, w1);
    binder1();
    w1.print();

    // 创建一个 std::reference_wrapper 对象，包装 w2 的引用
    auto binder2 = bind(&update, std::ref(w2));
    binder2();
    w2.print();

    // lambda reference capture Widget object
    auto lambda = [&](Widget & w) { w.no += 1; };
    cout << "lambda:" << sizeof(lambda) << endl;
    lambda(w1);
    w1.print();
}
