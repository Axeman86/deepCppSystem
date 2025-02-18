/**
 * @file 12_consteval4.cpp
 * @brief 对比不同返回值修饰的函数，编译时、运行时、编译时 OR 运行时初始化的区别
 *     1. squareR: 运行时初始化, 返回值在运行时确定
 *     2. squareC: 编译时初始化, consteval 修饰, 返回值必须在编译时确定
 *     3. squareCR: 编译时 OR 运行时初始化, constexpr 修饰, 返回值在编译时或运行时确定, 根据上下文确定是否在编译时计算;
 * @author Albert
 * @version 1.0
 * @date 2025-02-18
 */
#include <array>
#include <iostream>

// 运行时
int squareR(int x)
{
    return x * x;
}

// 编译时
consteval int squareC(int x)
{
    return x * x;
}

// 编译时 OR 运行时
constexpr int squareCR(int x)
{
    return x * x;
}

int main()
{
    {
        int data = 10;
        int i    = data * 2;
        std::cout << squareR(i) << '\n';  // OK
        std::cout << squareCR(i) << '\n'; // OK
        // std::cout << squareC(i) << '\n';       // ERROR
    }

    {
        constinit static int ci = 42;
        ci++;
        // ce++;

        std::cout << squareR(ci) << '\n';  // OK
        std::cout << squareCR(ci) << '\n'; // OK
        // std::cout << squareC(ci) << '\n';       // ERROR
    }

    {
        constexpr int ce = 42;
        std::cout << squareR(ce) << '\n';  // OK
        std::cout << squareCR(ce) << '\n'; // OK
        std::cout << squareC(ce) << '\n';  // OK:
    }

    // std::array<int, squareR(42)> arr1;   // ERROR
    std::array<int, squareCR(42)> arr2; // OK:
    std::array<int, squareC(42)> arr3;  // OK:
    // std::array<int, squareC(i)> arr4;    // ERROR
}
