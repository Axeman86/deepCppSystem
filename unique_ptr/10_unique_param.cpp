/**
 * @file 10_unique_param.cpp
 * @brief unique_ptr 作为函数参数的使用方法, 传递所有权, 传递引用, 传递指针, 传递const引用等
 *              所有权转移的本质是：调用移动操作符，将资源的所有权从一个对象转移到另一个对象，这个过程中，资源的所有权只能属于一个对象；
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

// 推荐：仅仅使用这个 widget，不表达任何所有权
void process1(Widget *)
{
    cout << "process1" << endl;
}
void process2(const Widget &)
{
    cout << "process2" << endl;
}

// 推荐，也常用：获取 widget 的所有权
void process3(unique_ptr<Widget>)
{
    cout << "process3" << endl;
}

// 可行，不常用：打算重新指向别的对象
void process4(unique_ptr<Widget> &)
{
    cout << "process4" << endl;
}

// 不推荐： 通常不是想要的
void process5(const unique_ptr<Widget> &)
{
    cout << "process5" << endl;
}

int main()
{
    unique_ptr<Widget> u = make_unique<Widget>();
    process1(u.get()); // 传递裸指针，不涉及所有权转移
    process2(*u);      // 传递引用，不涉及所有权转移
    process3(move(u)); // unique_ptr 的所有权从 u 转移到 process3 的参数中，但这不会触发 Widget 的移动构造函数，
                       // 因为只是 unique_ptr 的所有权发生了变化。
    process4(u); // 传递引用，可以重新指向别的对象, 但不涉及所有权转移
    process5(u); // 传递 const 引用，不涉及所有权转移
}
