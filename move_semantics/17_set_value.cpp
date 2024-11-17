/**
 * @file 17_set_value.cpp
 * @brief 使用 lvalue or rvalue 结合 std::move() 函数来赋值时的优化
 * @author Albert
 * @version 1.0.0
 * @date 2024-10-26
 */
#include <iostream>
#include <vector>
using namespace std;

struct Widget
{
    Widget() { cout << "ctor" << endl; }

    Widget(const Widget & rhs) { cout << "copy ctor" << endl; }

    Widget & operator=(const Widget & rhs)
    {
        cout << "copy assignment" << endl;
        return *this;
    }

    Widget(Widget && rhs) noexcept { cout << "move ctor" << endl; }

    Widget & operator=(Widget && rhs) noexcept
    {
        cout << "move assignment" << endl;
        return *this;
    }

    ~Widget() { cout << "dtor" << endl; }
};

struct MyClass
{
#ifdef NON_MOVE_SEMANTICS
#ifdef NON_TMPLATE
    // 模版实例化后的二种具体实现
    void setValue(const Widget & w)
    {
        //....
        //....
        m_w = w; //左值 copy assignment
    }

    void setValue(Widget && w)
    {
        //....
        //....
        m_w = std::move(w); //右值 move assignment
    }
#else
    /*
     * 使用完美转发模式：
     * 1. 传递左值，调用 copy assignment
     * 2. 传递右值，调用 move assignment
     * */
    template <typename T>
    void setValue(T && t)
    {
        //....
        //....
        m_w = std::forward<T>(t);
    }
    // tmeplate 特化
    template <>
    void setValue(const Widget & w)
    {
        m_w = w;
    }
    template <>
    void setValue(Widget && w)
    {
        m_w = std::move(w);
    }
#endif
#else
    // 1. 如果传递左值，先copy constructor，后 move assignment
    // 2. 如果传递右值，copy ctor removed，直接move assignment
    // 所以如果使用右值引用来赋值，则可以省去拷贝构造的调用
    void setValue(Widget w)
    {
        m_w = std::move(w);
    }
#endif

    Widget m_w;
};

int main()
{
    MyClass c;
    cout << "block 0-----" << endl;
    {
        Widget w;
        c.setValue(w);
    }
    cout << "block 1-----" << endl;
    {
        c.setValue(Widget{});
    }
    cout << "block 2-----" << endl;
}
