/**
 * @file 10_consteval2.cpp
 * @brief
 *   类成员函数使用 constexpr 关键字来修复返回值，根据上下文来确定返回值是否在编译时计算
 *     primeNumbers 函数中使用了动态内存分配（new 和 delete）， 这在 C++17 的constexpr 函数中是不允许的。
 *     constexpr 函数要求所有操作都必须在编译时完成，而动态内存分配只能在运行时完成。
 *     因此，这段代码实际上不能在编译期计算出结果。
 *   类成员函数使用 conseval 关键字来修饰返回值，则可以在编译期支持动态内存分配 new 和 delete, 但是也必须在编译器进行内存释放;
 * @author Albert
 * @version 1.0
 * @date 2025-02-18
 */
#include <array>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <vector>

using namespace std;

struct MyClass
{
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
};

template <int Num>
constexpr std::array<int, Num> primeNumbers()
// consteval std::array<int, Num> primeNumbers()
{
    // use dynamic memory allocation
    MyClass * mc = new MyClass();
    // std::unique_ptr 的析构函数不是 constexpr 的，因此不能在编译时使用智能指针进行动态内存分配。
    // unique_ptr<MyClass> mc = make_unique<MyClass>();

    std::array<int, Num> primes;
    int idx = 0;
    for (int val = 1; idx < Num; ++val)
    {
        if (mc->isPrime(val))
        {
            primes[idx++] = val;
        }
    }

    // release memory
    delete mc;

    return primes;
}

int main()
{
    constexpr array<int, 10> primes1 = primeNumbers<10>();
    static_assert(primes1.size() == 10, "size error");
    static_assert(primes1[0] == 2, "value error");
    static_assert(primes1[1] == 3, "value error");
    static_assert(primes1[2] == 5, "value error");
    static_assert(primes1[3] == 7, "value error");
    static_assert(primes1[4] == 11, "value error");
    static_assert(primes1[5] == 13, "value error");
    static_assert(primes1[6] == 17, "value error");
    static_assert(primes1[7] == 19, "value error");
    static_assert(primes1[8] == 23, "value error");
    static_assert(primes1[9] == 29, "value error");

    for (auto v : primes1)
    {
        std::cout << v << '\n';
    }
}
