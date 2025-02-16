/**
 * @file 4_constexpr4.cpp
 * @brief 通过模板特化，来确定编译时常量选择具体的类
 * @author Albert
 * @version 1.0
 * @date 2025-02-16
 */
#include <forward_list>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

// Determine return value when compile-time only
// 质数是指大于 1 的自然数，除了 1 和它本身外，不能被其他自然数整除
constexpr bool isPrime(unsigned int p)
{
    for (unsigned int d = 2; d <= p / 2; ++d)
    {
        if (p % d == 0)
        {
            return false;
        }
    }
    return p > 1;
}

template <int size, bool = isPrime(size)>
struct Widget
{
};

template <int SZ>
struct Widget<SZ, true>
{
    int data;

    void print() { cout << data << endl; }
};

template <int SZ>
struct Widget<SZ, false>
{
    double value;

    void process() { cout << value << endl; }
};

int main()
{
    Widget<10> w1;
    w1.value = 100.234;
    w1.process();

    Widget<17> w2;
    w2.data = 300;
    w2.print();
}
