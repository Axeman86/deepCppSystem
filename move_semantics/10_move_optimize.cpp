/**
 * @file 10_move_optimize.cpp
 * @brief 使用移动语义优化 vector 和 array 的赋值操作
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-17
 */
#include <array>
#include <iostream>
#include <vector>
using namespace std;

class Widget
{
public:
    Widget() : data_ptr(new int(1)) { cout << "Widget ctor" << endl; }
    ~Widget() { delete (data_ptr); }

    Widget(const Widget & rhs) noexcept
    {
        cout << "copy ctor" << endl;
        data     = rhs.data;
        data_ptr = new int(*rhs.data_ptr);
    }

    Widget & operator=(const Widget & rhs) noexcept
    {
        cout << "copy assignment" << endl;
        if (this == &rhs)
        {
            return *this;
        }

        Widget temp(rhs);
        swap(data, temp.data);
        swap(data_ptr, temp.data_ptr);

        return *this;
    }

    Widget(Widget && rhs) noexcept
    {
        cout << "move ctor" << endl;
        data         = rhs.data;
        data_ptr     = rhs.data_ptr;
        rhs.data_ptr = nullptr;
    }

    Widget & operator=(Widget && rhs) noexcept
    {
        cout << "move assignment" << endl;
        if (this == &rhs)
        {
            return *this;
        }
        Widget temp(move(rhs));
        swap(data, temp.data);
        swap(data_ptr, temp.data_ptr);

        return *this;
    }

private:
    int data = 1;
    int * data_ptr;
};

vector<Widget> getVec()
{
    return vector<Widget>(10);
}

array<Widget, 20> getArr()
{
    return array<Widget, 20> {};
}

int main()
{
    vector<Widget> vm;
    vm = getVec(); // 移动赋值 vector, 移动赋值(vm里的指针)
    cout << "---------" << endl;

    array<Widget, 20> am;
    am = getArr(); // 移动赋值 array, 移动赋值(am里的元素)
    cout << "---------" << endl;

    vector<Widget> vw;
    for (int i = 0; i < 30; i++)
    {
        vw.emplace_back(); // 元素移动
                           // vector 扩容时，元素会被移动, 会调用移动构造函数；如果没有移动构造函数，会调用拷贝构造函数;
        cout << vw.size() << " / " << vw.capacity() << endl; // vector 扩容算法是 2倍扩容
    }
}
