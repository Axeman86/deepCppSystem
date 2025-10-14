/**
 * @file 1_SFINAE.cpp
 * @brief SFINAE (Substitution Failure Is Not An Error) 机制: Function return type
 *     通过**函数返回值**类型来选择重载函数，如果函数返回值类型不匹配，编译器会选择其他重载函数
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

// return value T 类型，如果 T 有 MyType 成员类型，就调用这个函数
template <typename T>
typename T::MyType process(const T & t) // SFINAE away for int     int::MyType
{
    typename T::MyType data = 100;
    cout << "const T& " << endl;

    return data;
}

// template <typename T>
// int  process(const T& t) //NO SFINAE
// {
//     typename T::MyType data=100;
//     cout<<"const T& "<<endl;

//     return data;
// }

int main()
{
    Widget w{ 100 };
    process(w);

    int data;
    process(data);
}
