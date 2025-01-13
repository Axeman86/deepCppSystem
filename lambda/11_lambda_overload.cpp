/**
 * @file 11_lambda_overload.cpp
 * @brief lambda overload: 通过重载 lambda 函数对象，实现对不同类型的数据进行处理
 *         std::visit 所有辨析发生在编译期，比面向对象运行时 visitor 模版性能更好，同时约束更少，灵活性更高；
 *         双重分发多态辨析发生在编译期：std::visit 会根据 variant 的类型，调用对应的 lambda 函数对象，然后 lambda 函数对象再根据
 * variant 的类型，调用对应的处理函数；
 * @author Albert
 * @version 1.0
 * @date 2025-01-06
 */

#include <iostream>
#include <memory>
#include <variant>
#include <vector>

using namespace std;

// #define _NOT_USE_LAMBDA_OVERLOAD
#ifdef _NOT_USE_LAMBDA_OVERLOAD
// #define _USE_MULTIPLE_INHERIT
#ifdef _USE_MULTIPLE_INHERIT
struct Lam1
{
    void operator()(int data) { cout << "int:" << data << endl; }
};

struct Lam2
{
    void operator()(double data) { cout << "double:" << data << endl; }
};

struct Lam3
{
    void operator()(bool data) { cout << "bool: " << data << endl; }
};

struct Lam4
{
    void operator()(string data) { cout << "string: " << data << endl; }
};

struct overloaded : Lam1, Lam2, Lam3, Lam4
{
    using Lam1::operator();
    using Lam2::operator();
    using Lam3::operator();
    using Lam4::operator();
};
#else
struct my_overloaded
{
    void operator()(int data) { cout << "int:" << data << endl; }
    void operator()(double data) { cout << "double:" << data << endl; }
    void operator()(bool data) { cout << "bool: " << data << endl; }
    void operator()(string data) { cout << "string: " << data << endl; }
};
#endif
#else
template <typename... Ts> // 这是一个可变参数模板，表示 Ts 可以是任意数量的任意类型
struct overloaded : Ts... // 继承了所有传入的类型 Ts
{
    using Ts::operator()...; // 继承父类所有 operator()(即:调用) 操作符
};

// 模版推导指南:使得你可以通过传递多个函数对象来自动推导 overloaded 的模板参数
template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>; // 自定义模板推导
#endif

int main()
{
    std::variant<int, double, bool, string> data;

#ifdef _NOT_USE_LAMBDA_OVERLOAD
#ifdef _USE_MULTIPLE_INHERIT
    overloaded lams;
#else
    my_overloaded lams;
#endif
#else
#if 0
    auto l1   = [](int d) { std::cout << "int: " << d << std::endl; };
    auto l2   = [](double d) { std::cout << "double: " << d << std::endl; };
    auto l3   = [](bool d) { std::cout << "bool: " << d << std::endl; };
    auto l4   = [](const std::string & d) { std::cout << "string: " << d << std::endl; };
    auto lams = overloaded{ l1, l2, l3, l4 };
#else
    auto lams = overloaded{ [](int d) { cout << "int:" << d << endl; }, [](double d) { cout << "double:" << d << endl; },
                            [](bool d) { cout << "bool: " << d << endl; }, [](string d) { cout << "string: " << d << endl; } };
#endif
#endif

    data = "hello"s;
    std::visit(lams, data);
    cout << "Run here finish!" << endl;
}
