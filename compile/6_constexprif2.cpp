/**
 * @file 6_constexprif2.cpp
 * @brief 通过 if constexpr 在编译期就判断选择不同类型的迭代器进行编译
 *     如果处理逻辑简单且集中，使用 if constexpr 可以使代码更加紧凑。
 *     如果处理逻辑复杂且分散，使用函数重载可以提高代码的可读性和维护性。
 * @author Albert
 * @version 1.0
 * @date 2025-02-16
 */
#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <vector>

using namespace std;

#define CONSTEXPRIF
#ifdef CONSTEXPRIF
// 如果处理逻辑简单且集中，使用 if constexpr 可以使代码更加紧凑
template <typename Iter>
void process(Iter start, Iter end)
{
    if constexpr (std::random_access_iterator<Iter>)
    {
        cout << "处理 random_access_iterator" << endl;
    }
    else if constexpr (std::bidirectional_iterator<Iter>)
    {
        cout << "处理 bidirectional_iterator" << endl;
    }
    else if constexpr (std::forward_iterator<Iter>)
    {
        cout << "处理 forward_iterator" << endl;
    }
    else if constexpr (std::input_iterator<Iter>)
    {
        cout << "处理 input_iterator" << endl;
    }
    else if constexpr (std::output_iterator<Iter, typename std::iterator_traits<Iter>::value_type>)
    {
        cout << "处理 output_iterator" << endl;
    }
    else
    {
        cout << "其他迭代器" << endl;
    }
}
#else
// is_output_iterator 是一个模板结构体，用于检测一个迭代器是否是输出迭代器。
// 它利用了 SFINAE（Substitution Failure Is Not An Error）技术来实现。
// 如果一个迭代器是输出迭代器，那么它的 value_type 成员类型是存在的。
// 默认情况下，is_output_iterator 继承自 std::false_type，表示 Iter 不是输出迭代器
template <typename Iter, typename = void>
struct is_output_iterator : std::false_type
{
};

// 如果 Iter 是输出迭代器，那么它的 value_type 成员类型是存在的
// std::void_t<typename std::iterator_traits<Iter>::value_type> 将会是 void，特化版本会被选择
template <typename Iter>
struct is_output_iterator<Iter, std::void_t<typename std::iterator_traits<Iter>::value_type>> : std::true_type
{
};

template <std::random_access_iterator Iter>
void process(Iter start, Iter end)
{
    cout << "处理 random_access_iterator" << endl;
}

template <std::bidirectional_iterator Iter>
void process(Iter start, Iter end)
{
    cout << "处理 bidirectional_iterator" << endl;
}

template <std::forward_iterator Iter>
void process(Iter start, Iter end)
{
    cout << "处理 forward_iterator" << endl;
}

template <std::input_iterator Iter>
void process(Iter start, Iter end)
{
    cout << "处理 input_iterator" << endl;
}

// 如果 is_output_iterator<Iter>::value 为 true，则 std::enable_if_t 将会是 void，函数签名有效
// 如果 is_output_iterator<Iter>::value 为 false，则 std::enable_if_t 将会导致替换失败，函数签名无效，编译器会选择其他重载版本
template <typename Iter>
std::enable_if_t<is_output_iterator<Iter>::value> process(Iter start, Iter end)
{
    cout << "处理 output_iterator" << endl;
}

template <typename Iter>
void process(Iter start, Iter end)
{
    cout << "其他迭代器" << endl;
}
#endif

int main()
{
    vector<int> v{ 1, 2, 3, 4, 5 };
    process(v.begin(), v.end());

    map<string, int> m{
        { "C++", 100 },
        { "Rust", 200 },
        { "GO", 300 },
    };
    process(m.begin(), m.end());

    forward_list<int> l = { 7, 5, 16, 8 };
    process(l.begin(), l.end());

    int data[] = { 1, 2, 3, 4, 5 };
    process(data, data + 5);
}
