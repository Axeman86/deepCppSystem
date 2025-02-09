/**
 * @file 7_enable_if_use2.cpp
 * @brief enable_if template use: 编译期间，编译器根据 member template function 的类型是否为字符串类型选择不同的构造函数
 * @author Albert
 * @version 1.0
 * @date 2025-02-09
 */
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

template <typename T>
using EnableIfString = std::enable_if_t<std::is_convertible_v<T, std::string>>;
/* using EnableIfString = typename enable_if<is_convertible_v<T, std::string>>::type; */

class Widget
{
private:
    std::string name;

public:
    template <typename T, typename U = EnableIfString<T>>
    /* template <typename T, typename U = enable_if_t<is_convertible_v<T, std::string>>> */
    explicit Widget(T && n) : name(std::forward<T>(n))
    {
        std::cout << "Widget(T&& n) " << name << "\n";
        std::cout << "Is string: " << std::boolalpha << (typeid(U) == typeid(void)) << std::endl;
    }

    /* template <typename T>
     * explicit Widget(T && n)
     * {
     *     std::cout << "Widget(T&& n) " << name << "\n";
     * } */

    Widget(const Widget & p) : name(p.name) { std::cout << "Widget (const Widget & p) " << name << "\n"; }
    Widget(Widget && p) : name(std::move(p.name)) { std::cout << "Widget (Widget&& p) " << name << "\n"; }
};

int main()
{
    using namespace std::string_literals;
    std::string text = "C++"s;
    Widget p1(text);
    Widget p2("Carbon");

    Widget p3(p1);
    Widget p4(std::move(p1));

    char arr[] = "Python";
    Widget p5(arr);

    // Widget p6(10); // error: no matching function for call to ‘Widget::Widget(int&)’
}
