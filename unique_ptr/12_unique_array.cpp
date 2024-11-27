/**
 * @file 12_unique_array.cpp
 * @brief unique_ptr 与数组的使用方法: unique_ptr<Widget[]>(new Widget[5]), make_unique<Widget[]>(5)
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-27
 */
#include <iostream>
#include <memory>
#include <vector>

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
    {
        cout << "======= default new[] and delete[] =========" << endl;
        Widget * pw = new Widget[10];

        delete[] pw;
    }

    {
        cout << "======= unique_ptr new[] and delete[] =========" << endl;
        // unique_ptr<Widget> upArr=unique_ptr<Widget>(new Widget[10]); //错误! delete, delete[]

        vector<Widget> vw{ 10 };

        /* use vector repalce */
        unique_ptr<Widget[]> upArr1 = std::unique_ptr<Widget[]>(new Widget[5]);

        for (int i = 0; i < 5; i++)
        {
            cout << upArr1[i].m_data << " ";
        }

        cout << "\n";
    }

    {
        cout << "======= make_unique new[] and delete[] =========" << endl;
        unique_ptr<Widget[]> upArr2 = make_unique<Widget[]>(5);
        for (int i = 0; i < 10; i++) //内存越界，行为未定义
        {
            upArr2[i].m_data++;
        }

        for (int i = 0; i < 20; i++)
        {
            cout << upArr2[i].m_data << ", ";
        }
        cout << "\n";
    }
}
