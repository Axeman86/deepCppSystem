/**
 * @file 6_enable_if_use1.cpp
 * @brief enable_if template use: 编译期间，编译器根据模板参数类型的大小选择不同的重载函数
 * @author Albert
 * @version 1.0
 * @date 2025-02-09
 */
#include <iostream>
#include <vector>

using namespace std;

struct Point
{
    double x;
    double y;
};

// template <typename T>
// void process(T t) {
//     cout<<" sizeof T <= 8  "<<endl;
// }

// template <typename T>
// void process(const T& t) {
//     cout<<" sizeof T > 8  "<<endl;
// }

template <typename T, std::enable_if_t<sizeof(T) <= 8> * = nullptr>
void process(T t)
{
    cout << " sizeof T <= 8  " << endl;
}

template <typename T, std::enable_if_t<(sizeof(T) > 8)> * = nullptr>
/* void process(T t) */
void process(const T & t)
{
    cout << " sizeof T > 8  " << endl;
}

int main()
{
    int data = 100;
    process(data);
    double pai = 3.1415;
    process(pai);
    Point * pt = new Point{ 10.1, 20.2 };
    process(pt);

    string text = "hello";
    process(text);

    cout << "sizeof Point: " << sizeof(Point) << endl;
    cout << "sizeof Point*: " << sizeof(Point *) << endl;
    Point point{ 10.1, 20.2 };
    process(point);
}
