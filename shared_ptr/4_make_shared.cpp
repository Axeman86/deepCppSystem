/**
 * @file 4_make_shared.cpp
 * @brief shared_ptr 的 make_shared 用例，避免内存泄漏，以及代码更加简洁，
 *        不需要手动delete，使用make_shared替代new关键字
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-01
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

void process(shared_ptr<Widget> sp1, shared_ptr<Widget> sp2)
{
    cout << boolalpha << is_rvalue_reference<decltype(sp1)>::value << endl;
    cout << boolalpha << is_lvalue_reference<decltype(sp2)>::value << endl;
    cout << boolalpha << is_volatile<decltype(sp2)>::value << endl;
}

void invoke() {}

int main()
{
    {
        cout << "-----Bad : 可能会有内存泄漏-----" << endl;
        // 不好：可能会泄漏
        auto p1 = new Widget();
        auto p2 = new Widget();
        shared_ptr<Widget> s1(p1);
        shared_ptr<Widget> s2(p2);

        // p1=new Widget();
        // shared_ptr<Widget>(p1);
        // p2=new Widget();
        // shared_ptr<Widget>(p2);
        process(s1, s2);
    }

    {
        cout << "-----Good : 但不太干净-----" << endl;
        // 好多了，但不太干净
        shared_ptr<Widget> sp1(new Widget());
        shared_ptr<Widget> sp2(new Widget());
        process(sp1, sp2);
    }

    {
        cout << "-----Very good : It is clean-----" << endl;
        // 最好，也很干净
        process(make_shared<Widget>(), make_shared<Widget>());
    }
}
