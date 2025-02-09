/**
 * @file 3_SFINAE.cpp
 * @brief SFINAE (Substitution Failure Is Not An Error) 机制:
 *     通过函数模板中的模板参数类型来选择重载函数，如果函数模板参数类型不匹配，编译器会选择其他重载函数
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

// if T type has MyType member type, call this function
template <typename T, typename Ts = typename T::MyType> // SFINAE way for int
int process(const T & t)
{
    int data = 100;
    cout << "const T& " << endl;

    return data;
}

int main()
{
    Widget w{ 100 };
    process(w);

    int data;
    process(data);
}
