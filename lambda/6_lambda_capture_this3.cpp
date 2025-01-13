/**
 * @file 6_lambda_capture_this3.cpp
 * @brief Reference capture: 以值捕获 this 指针，相当于[this]，实际是以传值的方式捕获 this 指针，效果等同于传引用捕获;
 *        实际是对this指针进行了浅拷贝，在不同的作用域中this指针失效
 * @author Albert
 * @version 1.0
 * @date 2025-01-03
 */

#include <iostream>
#include <vector>

using namespace std;

// struct lambda{
//     Point* this;
//
//     void operator ()(){
//             this->x++;
//             this->y++;
//
//     };
// };

class Point
{
public:
    double x, y;

    auto invoke()
    {
        // reference capture
        auto lamb = [this]() {
            x++;
            y++;
            cout << x << ',' << y << endl;
        };
        return lamb;
    }
};

// 返回 lambda 表达式
auto process()
{
    Point p1{ 100, 200 };
    // lambda 的生命周期跟 p1 一样长
    auto lambda = p1.invoke();
    return lambda; // 返回一个 lambda 表达式, p1 被销毁, 对应的 this 指针失效
}

int main()
{
    // 不同的作用域
    auto lam = process();
    // Segmentation fault (core dumped)
    lam();
}
