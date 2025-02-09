/**
 * @file 5_enable_if_imple.cpp
 * @brief enable_if template implementation
 *     std::enable_if 是 SFINAE（Substitution Failure Is Not An Error，替换失败不是错误）的一种实现方式。
 *     SFINAE 是 C++ 模板编程中的一个重要特性，它允许在模板实例化过程中，如果某些条件不满足，编译器不会报错，
 *     而是会选择其他合适的模板实例化
 * @author Albert
 * @version 1.0
 * @date 2025-02-09
 */

#include <complex>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

using namespace std;

namespace MyLib {
// default template _TP argument is void
template <bool, typename _Tp = void>
struct enable_if
{
};

template <typename _Tp>
struct enable_if<true, _Tp>
{
    using type = _Tp;
};

// C++ 14提供, default template argument void
template <bool _Bp, typename _Tp = void>
using enable_if_t = typename enable_if<_Bp, _Tp>::type;

} // namespace MyLib

struct MyClass
{
};

int main()
{
    using Type1 = MyLib::enable_if<false>;
    // using T1= Type1::type; // 无type类型可取
    // using T1=MyLib::enable_if<false>::type;

    using Type2 = MyLib::enable_if<true>;
    using T2    = Type2::type; // void

    using Type3 = MyLib::enable_if<false, MyClass>;
    // using T3= Type3::type; // ? 无类型可取

    using Type4 = MyLib::enable_if<true, MyClass>;
    using T4    = Type4::type; //?  MyClass

    MyLib::enable_if_t<true, int> i = 100;
    // MyLib::enable_if_t<false, int> j = 100; // error: no type named 'type' in 'struct MyLib::enable_if<false, int>'
}
