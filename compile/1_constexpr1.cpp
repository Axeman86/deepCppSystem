/**
 * @file 1_constexpr1.cpp
 * @brief constexpr return value: 编译时常量和运行时常量
 *     可以是编译器期常量，也可以是运行期常量
 *     根据上下文，编译器会自动判断
 *     实参为编译时常量时，constexpr int value = 10; 返回值为编译时常量
 *     实参为运行时常量时，int value = 10; 返回值为运行时常量
 * @author Albert
 * @version 1.0
 * @date 2025-02-15
 */
#include <array>
#include <iostream>
#include <vector>
using namespace std;

// 可以是编译器期常量，也可以是运行期常量
// 根据上下文，编译器会自动判断
// 实参为编译时常量时，constexpr int value = 10; 返回值为编译时常量
// 实参为运行时常量时，int value = 10; 返回值为运行时常量
constexpr int fib(int n)
{
    if (n <= 2)
    {
        return 1;
    }
    else
    {
        return fib(n - 1) + fib(n - 2);
    }
}

int main()
{
    {
        cout << "Compile time constant" << endl;
        const int d1 = 100;                                       //编译时常量
        int myarray1[d1];                                         // 栈数组要求 size编译时确定大小
        cout << "sizeof(myarray1): " << sizeof(myarray1) << endl; // 400
        static_assert(sizeof(myarray1) == 400, "Compile time error");
    }

    {
        cout << "Run time constant" << endl;
        int value = 100;                                          // 运行时常量
        int myarray1[value];                                      // 栈数组要求 size 编译时确定大小
        cout << "sizeof(myarray1): " << sizeof(myarray1) << endl; // 400
        // static_assert(sizeof(myarray1) == 400, "Compile time error"); // 编译时错误
    }

    {
        cout << "Run time constant" << endl;
        long value        = 30;
        const long value2 = value;
        int myarray2[value2];                                     // C++ 中是错误, C 中是正确（栈变长数组）
        cout << "sizeof(myarray2): " << sizeof(myarray2) << endl; // 4 * 30 = 120
        // static_assert(sizeof(myarray2) == 120, "Compile time error"); // 编译时错误
    }

    {
        cout << "Compile time constant" << endl;
        const int d1 = 100;
        array<int, d1> myArray1;
        cout << "sizeof(myArray1): " << sizeof(myArray1) << endl; // 400
        static_assert(sizeof(myArray1) == 400, "Compile time error");
        constexpr int d2 = 100;
        array<int, d2 * 1024> myArray2;
        cout << "sizeof(myArray2): " << sizeof(myArray2) << endl; // 409600
        static_assert(sizeof(myArray2) == 409600, "Compile time error");
    }

    {
        cout << "Compile time constant" << endl;
        // 1,1,2,3,5,8,13,21,34,55
        constexpr int f6 = fib(6);
        cout << f6 << endl;
        static_assert(f6 == 8, "Compile time error");

        // 编译期计算出结果，递归调用
        constexpr int size2 = fib(20);
        cout << "size2 value " << size2 << endl;
        static_assert(size2 == 6765, "Compile time error");
        array<int, fib(10)> myArray;
        cout << "sizeof(myArray): " << sizeof(myArray) << endl; // 400
        static_assert(sizeof(myArray) == 220, "Compile time error");
    }

    {
        cout << "Run time constant" << endl;
        int data = 10;
        int f10  = fib(data);
        // static_assert(f10 == 55, "Compile time error"); // Compile time error
        cout << "f10 value " << f10 << endl;

        vector<int> vec(fib(data)); //要求运行期，不强制编译期
        cout << "vec size " << vec.size() << endl;
    }
}
