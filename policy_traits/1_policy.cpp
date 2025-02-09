/**
 * @file 1_policy.cpp
 * @brief 设计习语 (Policy Design) 策略模式: 将一个类或算法的设计分解为各个 policy，找到正交分解点;
 *     通过传入模板参数类型__Compare: 函数指针/函数对象/Lambda表达式 等方式，实现策略模式, 使得 Mysort 函数具有不同的行为
 * @author Albert
 * @version 1.0
 * @date 2025-01-26
 */
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

template <typename InputIterator, typename Function>
inline void foreach (InputIterator first, InputIterator last, Function f)
{
    for (; first != last; ++first)
    {
        f(*first);
    }
}

// Function pointer
using FPointer = void (*)(int, int);

template <typename T>
bool Compare(T x, T y)
{
    return x > y;
}

// Function object
template <typename T>
struct Greater
{
    bool operator()(T x, T y) { return x > y; }
};

struct Less
{
    bool operator()(int x, int y) { return x < y; }
};

// 通过传入模板参数类型__Compare:函数指针/函数对象/Lambda表达式等的方式，实现策略模式, 使得Mysort函数具有不同的行为
template <typename _RandomAccessIterator, typename _Compare>
inline void Mysort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp)
{
    if (__first != __last)
    {
        for (_RandomAccessIterator __next = __first + 1; __next != __last; ++__next)
        {
            if (__comp(*__next, *__first))
            {
                std::iter_swap(__first, __next);
            }
        }
    }
}

int main()
{
    cout << "Policy Design" << endl;
    vector<int> c = { 1, 2, 3, 4, 5 };

    foreach (c.begin(), c.end(), [](auto data) { cout << data << ", "; })
        ;
    cout << endl;

    // 函数指针
    cout << "Function Pointer" << endl;
    Mysort(c.begin(), c.end(), Compare<int>);
    foreach (c.begin(), c.end(), [](auto data) { cout << data << ", "; })
        ;
    cout << endl;

    // 函数对象
    cout << "Function Object" << endl;
    Mysort(c.begin(), c.end(), Less{});
    foreach (c.begin(), c.end(), [](auto data) { cout << data << ", "; })
        ;
    cout << endl;

    Mysort(c.begin(), c.end(), Greater<int>{});
    foreach (c.begin(), c.end(), [](auto data) { cout << data << ", "; })
        ;
    cout << endl;

    // Labmda Expression
    cout << "Lambda Expression" << endl;
    Mysort(c.begin(), c.end(), [](int x, int y) { return x < y; });

    foreach (c.begin(), c.end(), [](auto data) { cout << data << ", "; })
        ;
    cout << endl;
}
