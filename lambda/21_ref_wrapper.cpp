#include <algorithm>
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

    value_default();
    cout << endl;
    ref_wrap();
    cout << endl;
    share_wrap();
}
