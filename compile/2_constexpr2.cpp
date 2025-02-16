/**
 * @file 2_constexpr2.cpp
 * @brief constexpr return value: 编译时常量和运行时常量
 *     根据初始化时的值，来判断是否是编译时常量
 *     所以，在设计函数的时候，尽量都使用 constexpr 修饰，让编译器自动判断是编译时常量还是运行时常量
 * @author Albert
 * @version 1.0
 * @date 2025-02-15
 */
#include <forward_list>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

class Complex
{
public:
    double re;
    double im;

    constexpr Complex(double r, double i) : re(r), im(i)
    {
        // return value of constexpr function, not used here runing program
        /* cout << "ctor" << endl; */
    }

    constexpr double get_re() const noexcept { return re; }

    constexpr double get_im() const noexcept { return im; }

    virtual void print() const
    { // virtual function is not set to constexpr
        cout << re << "+" << im << "i" << endl;
    }
};

constexpr Complex operator+(const Complex & c1, const Complex & c2)
{
    return Complex(c1.re + c2.re, c1.im + c2.im);
}

int main()
{
    // 变量类型定义为 constexpr 修饰的 Complex 类型的 c1 c2 c3 变量，编译器会在编译期计算，而不是运行期；
    // constexpr 类型的变量，必须在编译期就能确定其值；
    // 所以，constexpr 类型的变量，必须是字面值类型，或者是一个 constexpr 函数的返回值；
    constexpr Complex c1{ 10.1, 20.2 };
    constexpr Complex c2{ 100.01, 200.02 };
    constexpr Complex c3 = c1 + c2;

    constexpr auto r = c3.get_re();
    static_assert(r == 110.11, "Compile time error");
    constexpr auto i = c3.get_im();
    static_assert(i == 220.22, "Compile time error");

    cout << "Run time constant" << endl;
    cout << c3.get_re() << "," << c3.get_im() << endl;
    c3.print();
}
