/**
 * @file 2_SFINAE.cpp
 * @brief SFINAE (Substitution Failure Is Not An Error) 机制:
 *     通过函数参数的类型来选择重载函数，如果函数参数的类型不匹配，编译器会选择其他重载函数
 * @author Albert
 * @version 1.0
 * @date 2025-02-09
 */
#include <iostream>
using namespace std;

struct Widget
{
    using MyType = int;

    int data;

    void increase() { data++; }
};

int process(...)
{
    int data = 100;
    cout << "..." << endl;

    return data;
}

// secend template parameter is a pointer type, if T has MyType member type, call this function
template <typename T>
int process(const T & t, typename T::MyType * p = nullptr) // SFINAE way for int, int::MyType
{
    typename T::MyType data = 100;
    cout << "const T& " << endl;

    return data;
}

int main()
{
    Widget w{ 100 };
    process(w); // int process(const Widget& t, int* p=nullptr)

    int data;
    process(data); // int process(...)
}
