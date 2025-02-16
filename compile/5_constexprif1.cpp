/**
 * @file 5_constexprif1.cpp
 * @brief 通过 if constexpr 来处理不同类型的迭代器, 替代函数重载
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

// #define TAG_DISPATCH
#ifdef TAG_DISPATCH
template <typename Iter>
using Iter_Category = typename iterator_traits<Iter>::iterator_category;

template <typename Iter>
void process_tag(Iter start, Iter end, forward_iterator_tag)
{
    cout << "处理 forward_iterator" << endl;
}

template <typename Iter>
void process_tag(Iter start, Iter end, random_access_iterator_tag)
{
    cout << "处理 random_access_iterator" << endl;
}

template <typename Iter>
void process_tag(Iter start, Iter end, bidirectional_iterator_tag)
{
    cout << "处理 bidirectional_iterator" << endl;
}

template <typename Iter>
void process_tag(Iter start, Iter end, output_iterator_tag)
{
    cout << "处理 output_iterator" << endl;
}

template <typename Iter>
void process_tag(Iter start, Iter end, input_iterator_tag)
{
    cout << "处理 input_iterator" << endl;
}

template <typename Iter>
void process(Iter start, Iter end)
{
    using iterator_category = typename iterator_traits<Iter>::iterator_category;

    process_tag(start, end, iterator_category{});
}
#else
template <typename Iter>
void process(Iter start, Iter end)
{
    using iterator_category = typename iterator_traits<Iter>::iterator_category;

    // process_tag(start, end, iterator_category{});

    if constexpr (std::is_same<iterator_category, random_access_iterator_tag>::value)
    {
        cout << "处理 random_access_iterator" << endl;
    }
    else if constexpr (is_same<iterator_category, bidirectional_iterator_tag>::value)
    {
        cout << "处理 bidirectional_iterator" << endl;
    }
    else if constexpr (is_same<iterator_category, forward_iterator_tag>::value)
    {
        cout << "处理 forward_iterator" << endl;
    }
    else if constexpr (is_same<iterator_category, output_iterator_tag>::value)
    {
        cout << "处理 output_iterator" << endl;
    }
    else if constexpr (is_same<iterator_category, input_iterator_tag>::value)
    {
        cout << "处理 input_iterator" << endl;
    }
    else
    {
        cout << "其他迭代器" << endl;
    }
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
