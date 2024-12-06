/**
 * @file 13_share_array.cpp
 * @brief shared_ptr<T[]> 管理动态数组; 由于没有没有 Array
 * 类型的元素个数的管理机制，所以很容易出现内存越界问题；就像原始的静态数组一样，shared_ptr<T[]> 也没有越界检查；
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-06
 */
#include <iostream>
#include <memory>

using namespace std;

struct Widget
{
    int m_data;

    Widget(int data = 1) : m_data(data) { cout << "ctor" << endl; }
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

int main()
{
    // shared_ptr<Widget> upArr=shared_ptr<Widget>(new Widget[10]); //错误!

    // vector<shared_ptr<Widget>> vw{10};

    shared_ptr<Widget[]> upArr1 = shared_ptr<Widget[]>(new Widget[5]);

    for (int i = 0; i < 5; i++)
    {
        cout << upArr1[i].m_data << " ";
    }

    cout << "\n";

    shared_ptr<Widget[]> upArr2 = shared_ptr<Widget[]>(new Widget[5]);
    for (int i = 0; i < 9; i++) //内存越界，行为未定义
    {
        upArr2[i].m_data++;
    }

    for (int i = 0; i < 10; i++)
    {
        cout << upArr2[i].m_data << " ";
    }
    cout << "\n";
}
