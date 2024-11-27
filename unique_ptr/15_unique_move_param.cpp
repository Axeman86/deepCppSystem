/**
 * @file 15_unique_move_param.cpp
 * @brief unique_ptr 作为函数参数的使用方法, 传递所有权, 传递引用, 传递指针, 传递const引用等
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-27
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

void process1(unique_ptr<Widget> w) // 传值，抢夺所有权
{
    cout << "inside process1" << endl;
    cout << w->m_data++ << endl;

    // unique_ptr<Widget> upw=std::move(w);
}

void process2(unique_ptr<Widget> & w) //传引用，不涉及所有权, 但是可以修改 w
{
    cout << "inside process4" << endl;
    cout << w->m_data++ << endl;

    /* unique_ptr<Widget> upw = std::move(w); */ // error, 不能转移所有权
}

void process3(const unique_ptr<Widget> & w) //传引用，不涉及所有权, 但是不可以修改 w, 但是可以修改 w->m_data
{
    cout << "inside process3" << endl;
    cout << w->m_data++ << endl; // error, 不能修改 w ?

    /* unique_ptr<Widget> upw = std::move(w); */ // error, const 不能转移所有权
}

void process4(unique_ptr<Widget> && w) //右值传引用，不涉及所有权, 但是可以修改 w
{
    cout << "inside process2" << endl;
    cout << w->m_data++ << endl;

    /* unique_ptr<Widget> upw = std::move(w); */ // error, 不能转移所有权
}

void process5(const Widget & w)
{
    cout << "inside process5" << endl;
    /* cout << w.m_data++ << endl; */ // error 不能修改 w
}

int main()
{
    cout << "------vlaue------" << endl;
    {
        unique_ptr<Widget> w{ new Widget(20) };
        /* process1(w); */ // error: delete copy operator
        process1(std::move(w));
        /* cout << "after:" << w->m_data << endl; */ // error, w 已经被转移
        cout << "outside process " << endl;
    }
    cout << "--------lvalue reference----------" << endl;
    {
        unique_ptr<Widget> w{ new Widget(50) };
        process2(w);
        cout << "after:" << w->m_data << endl;
        cout << "outside process" << endl;
    }
    cout << "--------const lvalue reference----------" << endl;
    {
        unique_ptr<Widget> w{ new Widget(40) };
        process3(std::move(w));
        cout << "after:" << w->m_data << endl;
        cout << "outside process" << endl;
    }
    cout << "------rvalue reference------" << endl;
    {
        unique_ptr<Widget> w{ new Widget(30) };
        process4(std::move(w));
        cout << "after:" << w->m_data << endl;
        cout << "outside process" << endl;
    }
}
