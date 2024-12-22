/**
 * @file 4_type_infer.cpp
 * @brief 模板参数类型自动推导:
 *        1. 引用性被忽略: 引用类型实参被单做非引用类型处理
 *        2. 值传递模板推导时，实参中的const/volatile修饰会被去掉;
 *        3. 引用转发时，左值参数会被转换为左值引用，右值参数会被转换为右值引用
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-16
 */
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
void process1(T & value)
{
    cout << value << endl;
}

template <typename T>
void process2(T value)
{
    cout << value << endl;
}

template <typename T>
void process3(T && value)
{
    cout << value << endl;
    if (is_rvalue_reference<decltype(value)>::value)
    {
        cout << "value is Right value reference " << endl;
    }
    else if (is_lvalue_reference<decltype(value)>::value)
    {
        cout << "value is Lift value reference " << endl;
    }
    else if (is_reference<decltype(value)>::value)
    {
        cout << "value is_reference " << endl;
    }
    else
    {
        cout << "value is not reference " << endl;
    }
}

int main()
{
    /* 模板类型推导 */
    int data1         = 100;
    int & data2       = data1;
    const int data3   = data1;
    const int & data4 = data1;

    // template<typename T>
    // void process1(T& value) 引用性被忽略, 引用类型实参被当作非引用类型处理
    process1(data1); //  T是int, value 是int&
    process1(data2); //  T是int, value 是int&
    process1(data3); //  T是const int, value 是const int&
    process1(data4); //  T是const int, value 是const int&
    cout << "--------" << endl;

    // template<typename T>
    // void process2(T value) 值传递模板推导时，实参中的const/volatile修饰会被去掉
    process2(data1); // T 是int, value 是 int
    process2(data2); // T 是int, value 是 int
    process2(data3); // T 是int, value 是 int
    process2(data4); // T 是int, value 是 int
    cout << "--------" << endl;

    // template<typename T>
    // void process3(T&& value) 引用转发时，左值参数会被转换为左值引用，右值参数会被转换为右值引用
    process3(data1);       // T 是int, value 是 int&
    process3(data2);       // T 是int, value 是 int&
    process3(data3);       // T 是const int, value 是 const int&
    process3(data4);       // T 是const int, value 是 const int&
    process3(move(data1)); // T 是int, value 是 int&&
}
