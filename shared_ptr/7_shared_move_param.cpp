/**
 * @file 7_shared_move_param.cpp
 * @brief shared_ptr 作为函数参数传递，传值、传引用、传const引用、传右值引用, 会改变引用计数吗？会改变指针的所有权吗？
 *        传值：会改变引用计数，会改变指针的所有权; 传其他三种不会改变引用计数，不会改变指针的所有权
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-03
 */
#include <iostream>
#include <memory>

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

void process1(shared_ptr<Widget> w) // 传值，成为共享所有权之一
{
    cout << "inside process1 " << w.use_count() << endl;
    shared_ptr<Widget> upw = w;
    cout << "inside process1 " << w.use_count() << ", data = " << upw->m_data++ << endl;
}

void process2(shared_ptr<Widget> & w) //传引用，不会改变引用计数
{
    cout << "inside process2 " << w.use_count() << endl;
    shared_ptr<Widget> upw = w;
    cout << "inside process2 " << upw.use_count() << ", data = " << upw->m_data++ << endl;
}

void process3(const shared_ptr<Widget> & w) //传const引用，不会改变引用计数
{
    cout << "inside process3 " << w.use_count() << endl;
    shared_ptr<Widget> upw = w;
    cout << "inside process3 " << upw.use_count() << ", data = " << upw->m_data++ << endl;
}

void process4(shared_ptr<Widget> && w) //右值传引用，不会改变引用计数
{
    cout << "inside process4 " << w.use_count() << endl;
    shared_ptr<Widget> upw = w;
    cout << "inside process4 " << upw.use_count() << ", data = " << upw->m_data++ << endl;
}

int main()
{
    cout << "------vlaue------" << endl;
    {
        shared_ptr<Widget> w{ new Widget(20) };
        cout << "before use count:" << w.use_count() << endl;
        process1(w);                       // Lvalue, copy operator
        process1(std::move(w));            // Rvalue, move operator
        process1(make_shared<Widget>(30)); // Rvalue, move operator, temp object
        cout << "after use count:" << w.use_count() << endl;
        /* destructor Widget */
        /* cout << "after:" << w->m_data << endl; */
        cout << "outside process " << endl;
    }
    cout << "--------lvalue reference----------" << endl;
    {
        shared_ptr<Widget> w{ new Widget(50) };
        cout << "before use count:" << w.use_count() << endl;
        process2((w));
        cout << "after use count:" << w.use_count() << ", data = " << w->m_data << endl;
        cout << "outside process" << endl;
    }
    cout << "--------const lvalue reference----------" << endl;
    {
        shared_ptr<Widget> w{ new Widget(40) };
        cout << "before use count:" << w.use_count() << endl;
        process3((w));
        process3(std::move(w));
        cout << "after use count:" << w.use_count() << ", data = " << w->m_data << endl;
        cout << "outside process" << endl;
    }
    cout << "------rvalue reference------" << endl;
    {
        shared_ptr<Widget> w{ new Widget(30) };
        cout << "before use count:" << w.use_count() << endl;
        process4(std::move(w));
        cout << "after use count:" << w.use_count() << ", data = " << w->m_data << endl;
        cout << "outside process" << endl;
    }
}
