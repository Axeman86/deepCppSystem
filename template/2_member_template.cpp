/**
 * @file 2_member_template.cpp
 * @brief The member template is a template that is a member of a class or class template.
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-15
 */
#include <iostream>
using namespace std;

template <typename T>
class Complex
{
    T re, im;

public:
    T real() const { return re; }
    T imag() const { return im; }

    Complex(T _re, T _im) : re{ _re }, im{ _im } {}

    // normal copy contructor
    Complex(const Complex & rhs) : re{ rhs.re }, im(rhs.im) { cout << "copy ctor" << endl; }

    // member template copy contructor
    template <typename U>
    Complex(const Complex<U> & c) : re{ static_cast<T>(c.real()) }, im{ static_cast<T>(c.imag()) }
    {
        cout << "memeber template" << endl;
    }

    // member template function
    template <typename U>
    void add(U r, U i) // 成员模板不可以是虚函数
    {
        cout << "member template add" << endl;
        this->re += r;
        this->im += i;
    }

    virtual void print() { cout << "[" << re << "," << im << "]" << endl; }
};

int main()
{
    Complex<int> c1{ 100, 200 };
    Complex<int> c3 = c1; // copy ctor

    Complex<double> c2{ 34.7, 89.9 };
    Complex<int> c4 = c2; // member template

    Complex c5{ 1000, 2000 };
    pair p1{ 100, 200 };

    c2.add(100, 200);
    c2.add(100.234, 200.234);
}
