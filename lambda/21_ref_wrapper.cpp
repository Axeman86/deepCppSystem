/**
 * @file 21_ref_wrapper.cpp
 * @brief std::reference_wrapper 是一个标准库模板类，用于包装引用，使其可以像对象一样进行拷贝、赋值操作
 *        它提供了一种将引用存储在容器（如 std::vector）中的方法，因为标准容器通常存储的是对象的副本，而不是引用。
 *        对比 Value semantics VS Reference semantics VS Shared semantics 三者的区别
 * @author Albert
 * @version 1.0
 * @date 2025-01-23
 */
#include <algorithm>
#include <functional> // std::reference_wrapper
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Widget
{
public:
    string name;
    int no;
    Widget(int _no, const std::string & _name) : no(_no), name(_name) {}

    void print() { cout << "[" << no << "] " << name << " "; }
};

void value_default()
{
    // 值语义
    cout << "Value semantics" << endl;
    vector<Widget> widgets;

    cout << "Widget size: " << sizeof(Widget) << endl; // 32 bytes
    Widget w1(100, "C++");
    Widget w2(200, "Java");

    // copy assignment
    widgets.push_back(w1);
    widgets.push_back(w2);
    widgets.push_back(w1);
    for (auto & widget : widgets)
    {
        widget.print();
    }

    cout << endl;

    w1.no++;
    w1.name = "GO";

    for (auto & widget : widgets)
    {
        widget.print();
    }

    cout << endl;
}

void ref_wrap()
{
    // 引用语义
    cout << "Reference semantics" << endl;
    // 包装一个类型为 Widget 的引用，使其可以像对象一样进行拷贝、赋值操作
    std::vector<std::reference_wrapper<Widget>> widgets;
    /* std::vector<Widget &> widgets; */ // error: reference object is defined Widget &, else is std::reference_wrapper<Widget>

    cout << "reference_wrapper<Widget> size: " << sizeof(std::reference_wrapper<Widget>) << endl; // 8 bytes
    Widget w1(100, "C++");
    Widget w2(200, "Java");

    // 引用栈对象，不会调用拷贝构造函数
    widgets.push_back(w1);
    widgets.push_back(w2);
    widgets.push_back(w1);
    for (auto & widget : widgets)
    {
        // 获取被包装的引用
        widget.get().print();
    }

    cout << endl;

    w1.no++;
    w1.name = "GO";

    for (auto & widget : widgets)
    {
        widget.get().print();
    }

    cout << endl;
}

void share_wrap()
{
    // 共享语义
    cout << "Share semantics" << endl;
    std::vector<std::shared_ptr<Widget>> widgets;

    cout << "shared_ptr<Widget> size: " << sizeof(std::shared_ptr<Widget>) << endl; // 16 bytes
    auto w1 = make_shared<Widget>(100, "C++");
    auto w2 = make_shared<Widget>(200, "Java");

    widgets.push_back(w1);
    widgets.push_back(w2);
    widgets.push_back(w1);
    for (auto & widget : widgets)
    {
        widget->print();
    }

    cout << endl;

    w1->no++;
    w1->name = "GO";

    for (auto & widget : widgets)
    {
        widget->print();
    }

    cout << endl;
}

int main()
{
    cout << "sizeof(int): " << sizeof(int) << endl;       // 4 bytes
    cout << "sizeof(string): " << sizeof(string) << endl; // 32 bytes
    cout << "sizeof(Widget): " << sizeof(Widget) << endl;
    cout << endl;

    value_default();
    cout << endl;
    ref_wrap();
    cout << endl;
    share_wrap();
}
