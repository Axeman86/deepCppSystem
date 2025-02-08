/**
 * @file 7_iterator_traits.cpp
 * @brief std::iterator_traits 是一个在C++标准库中定义的模板类，用于提取迭代器的属性;
 *     它是泛型编程的重要工具，允许编写与迭代器类型无关的代码;
 * @author Albert
 * @version 1.0
 * @date 2025-02-08
 */
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace custom {
// std::iterator_traits 提供了一种标准化的方法来访问迭代器的类型信息。它定义了五种类型：
template <typename Iterator>
struct iterator_traits
{
    // 迭代器的类别（例如，输入迭代器、输出迭代器、前向迭代器、双向迭代器、随机访问迭代器）
    using iterator_category = typename Iterator::iterator_category;
    // 迭代器所指向的值的类型
    using value_type = typename Iterator::value_type;
    // 用于表示两个迭代器之间的距离
    using difference_type = typename Iterator::difference_type;
    // 迭代器的指针类型
    using pointer = typename Iterator::pointer;
    // 迭代器的引用类型
    using reference = typename Iterator::reference;
};

// 特化版本，用于处理原生指针类型
template <typename T>
struct iterator_traits<T *>
{
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = T *;
    using reference         = T &;
    using iterator_category = std::random_access_iterator_tag;
};

// 特化版本，用于处理 const 原生指针类型
template <typename T>
struct iterator_traits<const T *>
{
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;
    using pointer           = const T *;
    using reference         = const T &;
    using iterator_category = std::random_access_iterator_tag;
};

} // namespace custom

template <typename Iter>
void print_iterator_trains(Iter it)
{
    using iterator_traits = custom::iterator_traits<Iter>;
    std::cout << "iterator_category: " << typeid(typename iterator_traits::iterator_category).name() << std::endl;
    std::cout << "value_type: " << typeid(typename iterator_traits::value_type).name() << std::endl;
    std::cout << "difference_type: " << typeid(typename iterator_traits::difference_type).name() << std::endl;
    std::cout << "pointer: " << typeid(typename iterator_traits::pointer).name() << std::endl;
    std::cout << "reference: " << typeid(typename iterator_traits::reference).name() << std::endl;
}

int main()
{
    std::vector<int> v{ 1, 2, 3, 4, 5 };
    print_iterator_trains(v.begin());

    std::cout << "----------------" << std::endl;
    float arr[] = { 1, 2, 3, 4, 5 };
    print_iterator_trains(arr);

    // 使用特化版本 传入原生指针
    std::cout << "----------------" << std::endl;
    std::vector<int> * p = &v;
    print_iterator_trains(p);

    std::cout << "----------------" << std::endl;
    auto itor = std::vector<int>::iterator::iterator_category();
    std::cout << std::is_same<decltype(itor), std::random_access_iterator_tag>::value << std::endl;

    return 0;
}
