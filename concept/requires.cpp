/**
 * @file requires.cpp
 * @brief requires (参数) { 表达式; ...; 表达式n; }
 * - 概念的名字（如 Addable）就像一个“类型特性标签”，它代表了一组用 requires 表达式描述的约束条件。
 * 概念是对类型约束的命名，requires 用于具体描述这些约束。概念的名字可以像类型一样用于模板参数的约束。
 * @author Albert
 * @version 1.0
 * @date 2026-01-08
 */
#include <iostream>
#include <vector>

namespace concept_requires {
/*
 * ### 1. requires 表达式（requires expression）
 * - requires 表达式：用于定义概念，描述类型需要满足的操作或性质。
 * **解析：**
 * 定义一个“概念”（Concept），名字叫 Addable
 * requires(T a, T b)：声明了两个 T 类型的变量 a 和 b
 * { a + b }：检查 a+b 这个表达式是否有效
 * -> std::convertible_to<T>：要求 a+b 的结果能转换为T类型
 */
template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

/*
 * ### 2. requires 子句（requires clause）
 * - requires 子句：用于约束模板或函数的可用性。
 */
template <typename T>
    requires Addable<T>
T add(T a, T b)
{
    return a + b;
}

template <Addable T>
T add2(T a, T b)
{
    return a + b;
}
} // namespace concept_requires

int main()
{
    using namespace concept_requires;

    std::cout << std::boolalpha;
    std::cout << "int is Addable: " << Addable<int> << std::endl;                           // true
    std::cout << "double is Addable: " << Addable<double> << std::endl;                     // true
    std::cout << "std::string is Addable: " << Addable<std::string> << std::endl;           // true
    std::cout << "std::vector<int> is Addable: " << Addable<std::vector<int>> << std::endl; // false

    return 0;
}
