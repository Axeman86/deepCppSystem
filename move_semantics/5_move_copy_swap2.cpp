/**
 * @file 5_move_copy_swap2.cpp
 * @brief copy and swap, copy assignment / move assignment 使用 swap 交换数据 之 值语义
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-21
 */
#include <iostream>
#include <vector>
using namespace std;

struct Point
{
    int x;
    int y;
};

struct Widget
{
    int value;
    Point * data;

    Widget(int _value = 0, int _x = 0, int _y = 0) : value(_value), data(new Point{ _x, _y }) { cout << "ctor" << endl; }

    ~Widget()
    {
        cout << "dtor :" << data << endl;
        delete data;
    }

    Widget(const Widget & rhs) : value(rhs.value), data(new Point(*rhs.data)) { cout << "copy ctor" << endl; }

    Widget(Widget && rhs) noexcept : value(rhs.value), data(rhs.data) // 1. 窃取源对象的指针值
    {
        // cout << "Widget rhs is rvalue " << boolalpha << is_rvalue_reference<decltype(rhs)>::value << endl;
        rhs.data = nullptr; // 2. 将源对象的值设为有效状态
        cout << "move ctor" << endl;
    }

    /*
     * 参数 rhs 是一个临时对象，因此可以作为左值也可以作为右值使用, 所以 rhs 即不是 Lvalue references 也不是 Rvalue references
     * 当传入左值时，会调用拷贝构造函数来创建 rhs。
     * 当传入右值时，会调用移动构造函数来创建 rhs。
     * 这意味着每次调用通用赋值运算符时，都会有一次额外的对象构造（拷贝或移动），这在某些情况下可能会带来性能开销。
     * rhs 是一个按值传递的参数，这意味着在函数调用时会创建一个临时对象，并在函数结束时销毁它。
     * */
    Widget & operator=(Widget rhs) noexcept
    {
        // rhs output all is false
        // cout << "Widget rhs is lvalue " << boolalpha << is_lvalue_reference<decltype(rhs)>::value << endl;
        // cout << "Widget rhs is lvalue " << boolalpha << is_lvalue_reference_v<decltype(rhs)> << endl; // __cplusplus >= 201703L
        // cout << "Widget rhs is rvalue " << boolalpha << is_rvalue_reference<decltype(rhs)>::value << endl;
        // cout << "Widget rhs is rvalue " << boolalpha << is_rvalue_reference_v<decltype(rhs)> << endl; // __cplusplus >= 201703L
        swap(value, rhs.value);
        swap(data, rhs.data);

        cout << "copy/move assignment" << endl;
        return *this;
    }

    void process() { cout << value << ": [" << data->x << "," << data->y << "]" << endl; }
};

/* The return vlaue is temporary objects */
Widget createWidget()
{
    Widget w(1, 10, 20);
    return w;
}

int main()
{
    {
        Widget w{ 3, 1000, 2000 };
        w = createWidget(); //移动赋值, Rvalue
    }

    cout << "------" << endl;
    {
        Widget w1{ 1, 10, 20 };
        Widget w2{ 2, 100, 200 };
        w2 = std::move(w1); //移动赋值, Rvalue
    }

    cout << "------" << endl;
    {
        Widget w1{ 1, 10, 20 };
        Widget w2{ 2, 100, 200 };
        w2 = w1; //拷贝赋值, Lvalue
    }

    cout << "------" << endl;
    {
        Widget w1{ 1, 10, 20 };
        Widget w2 = std::move(w1); // 移动构造, Rvalue
    }
    cout << "------" << endl;
    {
        Widget w1 = createWidget(); // return value 优化, 本应移动构造、但编译器执行了拷贝消除
    }

    cout << "------" << endl;
    {
        Widget w1{ 1, 10, 20 };
        w1 = w1; // 自赋值, Lvalue
    }
    cout << "------" << endl;
    {
        Widget w1{ 1, 10, 20 };
        w1 = std::move(w1); // 移动自赋值, Rvalue
    }
}
