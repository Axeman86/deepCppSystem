/**
 * @file 7_constexprif3.cpp
 * @brief 通过 if constexpr 可使变参模板的实现代码更加简洁
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
// #define OLD

// 传统的变参模板实现方式
#ifdef OLD
void print(void) {}

template <typename T, typename... TT>
void print(T firstArg, TT... args)
{
    cout << firstArg << endl;
    print(args...);
}

// void print (int , string, double, bool);
// void print (string, double, bool);
// void print (double, bool);
// void print (bool);
#else
template <typename T, typename... Types>
void print(T const & firstArg, Types const &... args)
{
    cout << firstArg << endl;
    if constexpr (sizeof...(args) > 0)
    {
        print(args...);
    }
}
// void print (int , string s, double d, bool b)
// {
//     cout << firstArg << endl;
//     print (s, d, b);
// }

// void print (string, double d, bool b)
// {
//     cout << firstArg << endl;
//     print (d, b);
// }
// void print (double, bool b)
// {
//     cout << firstArg << endl;
//     print (b);

// }
// void print (bool)
// {
//     cout << firstArg << endl;
// }
#endif
int main()
{
    print(100, "hello"s, 30.46, true);
}
