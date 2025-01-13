/**
 * @file 12_base_init.cpp
 * @brief base init: 通过继承的方式，实现对多个结构体的初始化
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

struct Object : WidgetA, WidgetB, WidgetC
{
    double mx;
};

int main()
{
    WidgetA a{ 1.1 };
    WidgetB b{ 2.2, 3.3 };
    WidgetC c{ 4.4, 5.5, 6.6 };

    Object obj{ a, b, c, 7.7 };

    cout << sizeof(obj) << endl;
    cout << obj.x << endl;
    cout << obj.y << endl;
    cout << obj.z << endl;
    cout << obj.u << endl;
    cout << obj.v << endl;
    cout << obj.w << endl;
    cout << obj.mx << endl;
}
