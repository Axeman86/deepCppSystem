/**
 * @file 13_unique_container.cpp
 * @brief unique_ptr 作为容器元素的使用方法: 使用make_unique代替new, 以及unique_ptr<T>代替T*
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

    Widget(int data) : m_data(data) {}
};

int main()
{
    // vector<unique_ptr<Widget>> v0{make_unique<Widget>(1), make_unique<Widget>(2)};

    vector<Widget *> v0;
    vector<unique_ptr<Widget>> v1;

    for (int i = 0; i < 10; i++)
    {
        v1.push_back(make_unique<Widget>(i));
    }

    for (auto & elem : v1)
    {
        cout << (*elem).m_data << ",";
    }
    cout << endl;

    vector<unique_ptr<Widget>> v2;
    for (auto && elem : v1)
    {
        cout << boolalpha << std::is_lvalue_reference<decltype(elem)>::value << " ";

        v2.push_back(std::move(elem));
    }
    cout << endl;

    for (auto && elem : v2)
    {
        cout << std::is_lvalue_reference<decltype(elem)>::value << " ";

        cout << (*elem).m_data << ",";
    }
    cout << endl;
}
