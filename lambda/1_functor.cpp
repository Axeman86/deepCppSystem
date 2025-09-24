/**
 * @file 1_functor.cpp
 * @brief function pointer Vs functor object Vs lambda expression
 *        1. function pointer: void (*)(int)
 *        2. functor object: struct IntPrinter{ void operator()(int data) const { } };
 *        3. lambda expression: [](auto data) { }; lambda expression is a function object
 *        函数对象是通过重载类的 operator() 调用操作符，实现类似函数的功能，将类对象当作函数使用的能力
 * @author Albert
 * @version 1.0
 * @date 2025-01-01
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename Container, typename F>
void foreach (Container c, F op)
{
    for (auto & data : c)
    {
        op(data);
    }
}

// function pointer
using FPointer = void (*)(int);
void print(int data)
{
    cout << data << " ";
}

// function object
struct IntPrinter
{
    void operator()(int data) const { cout << data << ","; }
};

// function template object
template <typename T>
struct Printer
{
    void operator()(T data) const { cout << data << ","; }
};

template <typename T>
bool compare(T x, T y)
{
    return x > y;
}

template <typename T>
class Comparer
{
public:
    bool operator()(T x, T y) { return x > y; }
};

/*
struct ___LambdaXXXX {
    void operator() (int data) const {
      cout << data <<"-";
    }
};

template<typename T>
struct ___LambdaXXXX {
    void operator() (T data) const {
      cout << data <<"-";
    }
};
*/

int main()
{
    vector v = { 7, 2, 8, 4, 3 };

    {
        FPointer p = print;
        p(100);
        foreach (v, p)
            ; // 函数指针
        cout << endl;
    }

    {
        IntPrinter intPter;
        intPter(100);
        foreach (v, intPter)
            ;
        cout << endl;
    }

    {
        Printer<int> pobj;
        pobj(100);

        foreach (v, pobj)
            ; // 函数对象 inline
        foreach (v, Printer<int>{})
            ;
        cout << endl;
    }

    {
        // foreach(v, ___LambdaXXXX{});
        foreach (v, [](auto data) { cout << data << ","; })
            ;
        cout << endl;
    }

    {
        // 函数指针
        sort(v.begin(), v.end(), compare<int>);
        // 函数对象
        sort(v.begin(), v.end(), Comparer<int>{});
        sort(v.begin(), v.end(), std::greater<int>{});

        // Labmda表达式
        sort(v.begin(), v.end(), [](auto x, auto y) -> bool { return x > y; });

        foreach (v, [](auto data) { cout << data << "-"; })
            ;
        cout << endl;
    }
}
