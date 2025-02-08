/**
 * @file 2_type_traits.cpp
 * @brief 类型特征 (Type Traits): 通过模板特化，对不同类型的数据进行类型推导，实现不同类型的输入，指定类型的输出功能;
 * @author Albert
 * @version 1.0
 * @date 2025-01-26
 */
#include <iostream>
#include <vector>

using namespace std;

struct Complex
{
    int re;
    int im;

    Complex(int _re = 0, int _im = 0) : re(_re), im(_im) {}
};

Complex operator+(const Complex & r1, const Complex & r2)
{
    return Complex(r1.re + r2.re, r1.im + r2.im);
}

// traits template
template <typename T>
struct SumTraits
{
    using ValueType = T;
};

// SumTraits 各种类型的特化版本
// 通过类型匹配，而选择相应的特化版本
template <>
struct SumTraits<char>
{
    using ValueType = int;
};

template <>
struct SumTraits<short>
{
    using ValueType = int;
};

template <>
struct SumTraits<int>
{
    using ValueType = long long;
};

template <>
struct SumTraits<unsigned int>
{
    using ValueType = unsigned long;
};

template <>
struct SumTraits<float>
{
    using ValueType = double;
};

// 模板函数, 传入的是什么类型，通过求和后返回的就是什么类型
template <typename T>
T sum0(T const * beg, T const * end)
{

    T total{};
    while (beg != end)
    {
        total += *beg;
        ++beg;
    }
    return total;
}

// template function: 通过传入的类型 T, 使用 SumTraits 模板定义的各种类型的特化版本，在编译时推导出对应的返回值类型
template <typename T>
auto sum1(T const * beg, T const * end)
{
    // 返回值类型
    using SumType = typename SumTraits<T>::ValueType;

    SumType total{};
    while (beg != end)
    {
        total += *beg;
        ++beg;
    }
    return total;
}

// ST = SumTraits<T>: 这是一个默认模板参数，表示 ST 默认是 SumTraits<T> 类型, 如果没有传入 ST 参数;
template <typename T, typename ST = SumTraits<T>>
auto sum2(T const * beg, T const * end)
{
    // 返回值类型
    typename ST::ValueType total{};
    while (beg != end)
    {
        total += *beg;
        ++beg;
    }
    return total;
}

// 如果没有找到 SumTraits 对应的特化版本，就使用非特化版本:using SumT = T ==> input type == output type;
template <typename Iter>
auto sum3(Iter start, Iter end)
{
    // 元素类型 define
    // std::iterator_traits 是一个标准库模板类，用于提取迭代器类型的相关信息。
    // Iter 是一个模板参数，表示某种迭代器类型。
    // std::iterator_traits<Iter>::value_type 是 std::iterator_traits<Iter> 中定义的一个类型成员，表示迭代器 Iter 所指向的值的类型。
    // typename 关键字用于告诉编译器，std::iterator_traits<Iter>::value_type 是一个类型，而不是一个静态成员或变量。
    using VT = typename std::iterator_traits<Iter>::value_type;

    // 返回值类型 define
    using SumType = typename SumTraits<VT>::ValueType;

    SumType total{};
    while (start != end)
    {
        total = total + *start;
        ++start;
    }
    return total;
}

int main()
{
    int num[]   = { 1, 2, 3, 4, 5 };
    char name[] = "templates";
    vector<int> vec{ 10, 20, 30, 40, 50 };

    cout << "sum0 function test:" << endl;
    int s0 = sum0(num, num + 5);
    int s1 = sum0(name, name + sizeof(name) - 1);
    cout << s0 << "," << s1 << endl;

    cout << "sum1 function test:" << endl;
    int s2 = sum1(num, num + 5);
    int s3 = sum1(name, name + sizeof(name) - 1);
    cout << s2 << "," << s3 << endl;

    cout << "sum2 function test:" << endl;
    int s4 = sum2(num, num + 5);
    int s5 = sum2(name, name + sizeof(name) - 1);
    cout << s4 << "," << s5 << endl;
    // error: no matching function for call to 'sum2(std::vector<int>::iterator, std::vector<int>::iterator)'
    // cout << sum2(vec.begin(), vec.end()) << endl;

    cout << "sum3 function test:" << endl;
    int s6 = sum3(num, num + 5);
    int s7 = sum3(name, name + sizeof(name) - 1);
    int s8 = sum3(vec.begin(), vec.end());
    cout << s6 << "," << s7 << "," << s8 << endl;

    cout << "sum3 function test for Complex:" << endl;
    vector<Complex> vc{ Complex{ 1, 2 }, Complex{ 3, 4 }, Complex{ 5, 6 } };
    Complex cp = sum3(vc.begin(), vc.end());
    cout << cp.re << "+" << cp.im << "i" << endl;
}
