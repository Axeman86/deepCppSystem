/**
 * @file 6_traits_tags.cpp
 * @brief std::iterator_traits 是标准库中的一个模板结构体，用于提取迭代器的相关类型信息
 * std::input_iterator_tag：
 *     表示输入迭代器。
 *     输入迭代器支持只读访问，可以进行单向遍历。
 *     典型的输入迭代器包括指向输入流的迭代器。
 *
 * std::output_iterator_tag：
 *     表示输出迭代器。
 *     输出迭代器支持只写访问，可以进行单向遍历。
 *     典型的输出迭代器包括指向输出流的迭代器。
 *
 * std::forward_iterator_tag：
 *     表示前向迭代器。
 *     前向迭代器支持读写访问，可以进行单向遍历，并且可以多次遍历相同的元素。
 *     典型的前向迭代器包括 std::forward_list 的迭代器。
 *
 * std::bidirectional_iterator_tag：
 *     表示双向迭代器。
 *     双向迭代器支持读写访问，可以进行双向遍历。
 *     典型的双向迭代器包括 std::list 的迭代器 and std::map 的迭代器。
 *
 * std::random_access_iterator_tag：
 *     表示随机访问迭代器。
 *     随机访问迭代器支持读写访问，可以进行双向遍历，并且可以直接跳转到任意位置。
 *     典型的随机访问迭代器包括 std::vector 和 std::deque 的迭代器。
 *
 * @author Albert
 * @version 1.0
 * @date 2025-02-07
 */
#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

// 模板类型的函数重载不需要显式指定类型，编译器会根据传递的参数类型自动推导
template <typename Iter>
void process_tag(Iter start, Iter end, forward_iterator_tag tag)
{
    cout << "处理 forward_iterator" << endl;
}

template <typename Iter>
void process_tag(Iter start, Iter end, random_access_iterator_tag tag)
{
    cout << "处理 random_access_iterator" << endl;
}

template <typename Iter>
void process_tag(Iter start, Iter end, bidirectional_iterator_tag tag)
{
    cout << "处理 bidirectional_iterator" << endl;
}

template <typename Iter>
void process_tag(Iter start, Iter end, output_iterator_tag tag)
{
    cout << "处理 output_iterator" << endl;
}

template <typename Iter>
void process_tag(Iter start, Iter end, input_iterator_tag tag)
{
    cout << "处理 input_iterator" << endl;
}

template <typename Iter>
using Iter_Category = typename iterator_traits<Iter>::iterator_category;

template <typename Iter>
void process(Iter start, Iter end)
{
    cout << "Use Iter_Category    : ";
    process_tag(start, end, Iter_Category<Iter>{});
}

template <typename Iter>
void process(Iter start, Iter end, void *)
{
    using iterator_category = typename iterator_traits<Iter>::iterator_category;

    cout << "Use iterator_category: ";
    process_tag(start, end, iterator_category{});
}

// 传统的 IF 判断模式写法, 用于对比, 与上面的 process 函数功能相同
// 但是代码冗余, 且不易维护，不易扩展; 建议使用函数重载的方式来实现，替代传统的 IF 判断模式
template <typename Iter>
void printIteratorCategory(Iter start, Iter end)
{
    if (is_same<Iter_Category<Iter>, forward_iterator_tag>::value)
    {
        process_tag(start, end, forward_iterator_tag{});
    }
    else if (is_same<Iter_Category<Iter>, random_access_iterator_tag>::value)
    {
        process_tag(start, end, random_access_iterator_tag{});
    }
    else if (is_same<Iter_Category<Iter>, bidirectional_iterator_tag>::value)
    {
        process_tag(start, end, bidirectional_iterator_tag{});
    }
    else if (is_same<Iter_Category<Iter>, output_iterator_tag>::value)
    {
        process_tag(start, end, output_iterator_tag{});
    }
    else if (is_same<Iter_Category<Iter>, input_iterator_tag>::value)
    {
        process_tag(start, end, input_iterator_tag{});
    }
}

int main()
{
    vector<int> v{ 1, 2, 3, 4, 5 };
    process(v.begin(), v.end());
    process(v.begin(), v.end(), nullptr);

    map<string, int> m{
        { "C++", 100 },
        { "Rust", 200 },
        { "GO", 300 },
    };
    process(m.begin(), m.end());
    process(m.begin(), m.end(), nullptr);

    list<int> lst = { 1, 2, 3, 4, 5 };
    process(lst.begin(), lst.end());
    process(lst.begin(), lst.end(), nullptr);

    forward_list<int> l = { 7, 5, 16, 8 };
    process(l.begin(), l.end());
    process(l.begin(), l.end(), nullptr);

    int data[] = { 1, 2, 3, 4, 5 };
    process(data, data + 5);
    process(data, data + 5, nullptr);

    array<int, 5> arr = { 1, 2, 3, 4, 5 };
    process(arr.begin(), arr.end());
    process(arr.begin(), arr.end(), nullptr);

    deque<int> dq = { 1, 2, 3, 4, 5 };
    process(dq.begin(), dq.end());
    process(dq.begin(), dq.end(), nullptr);

    printIteratorCategory(v.begin(), v.end());

    return 0;
}
