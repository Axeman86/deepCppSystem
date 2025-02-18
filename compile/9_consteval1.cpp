/**
 * @file 9_consteval1.cpp
 * @brief consteval关键字的使用，编译时计算，返回值必须在编译时确定
 * @author Albert
 * @version 1.0
 * @date 2025-02-18
 */
#include <array>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

// 根据上下文，constexpr 关键字用于指示函数或对象的值在编译时计算。
// 如果返回的值是在编译时常量，则传入的值也必须是在编译时常量。
// 如果返回的值是在运行时计算的，则传入的值可以是在运行时计算的常量。
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

// consteval 函数保证在编译时执行，并且其结果必须在编译时确定。
// primeNumbers 函数是一个 consteval 函数，因此它在编译时生成包含指定数量质数的 std::array。
template <int Num>
consteval std::array<int, Num> primeNumbers()
{
    std::array<int, Num> primes;
    int idx = 0;
    for (int val = 1; idx < Num; ++val)
    {
        if (isPrime(val))
        {
            primes[idx++] = val;
        }
    }
    return primes;
}

int main(void)
{
    constexpr int data = 11;
    cout << data << " is prime:" << boolalpha << isPrime(data) << endl;

    auto primes1 = primeNumbers<data>();

    for (auto v : primes1)
    {
        std::cout << v << '\n';
    }
}
