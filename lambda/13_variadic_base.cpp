/**
 * @file 13_variadic_base.cpp
 * @brief 通过模版推导的方式，来实现对单个基类的继承和初始化
 * @author Albert
 * @version 1.0
 * @date 2025-01-06
 */

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct WidgetA
{
    double x;
};

struct WidgetB
{
    double y;
    double z;
};

struct WidgetC
{
    double u;
    double v;
    double w;
};

template <typename... Base>
struct Object : public Base...
{
    double mx;
};

// template<class T1>
// struct Object: T1{
// };

// template<class T1, class T2>
// struct Object: T1, T2{
// };

// template<class T1, class T2, class T3>
// struct Object: T1, T2, T3{
// };

template <typename... T>
Object(T...) -> Object<T...>; // 模板推导的get，编译器在看到 Object(T...)时，必须要知道我实际是想使用 Object<T...> 这个类型的,
                              // 表示将类型参数包T展开，并用于构造Object类的实例;
                              // 例如使用 Object obj{a, b, c}，编译器会推导出 Object<WidgetA, WidgetB, WidgetC> obj{a, b, c};

int main()
{
    WidgetA a{ 1.1 };
    WidgetB b{ 2.2, 3.3 };
    WidgetC c{ 4.4, 5.5, 6.6 };

    Object obj{ a, b, c }; // <===>
    /* Object<WidgetA, WidgetB, WidgetC> obj{ a, b, c }; */

    cout << sizeof(obj) << endl;
    cout << obj.x << endl;
    cout << obj.y << endl;
    cout << obj.z << endl;
    cout << obj.u << endl;
    cout << obj.v << endl;
    cout << obj.w << endl;
    cout << obj.mx << endl;
}
