/**
 * @file 6_constexprif2.cpp
 * @brief 通过 if constexpr 在编译期就判断选择不同类型的迭代器进行编译
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

// template<random_access_iterator Iter>
// void process (Iter start, Iter end )
// {
//     cout<<"处理 random_access_iterator"<<endl;
// }

// template<bidirectional_iterator Iter>
// void process (Iter start, Iter end )
// {
//     cout<<"处理 bidirectional_iterator"<<endl;
// }

// template<typename Iter>
// void process (Iter start, Iter end )
// {
//     cout<<"处理其他迭代器"<<endl;
// }

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
