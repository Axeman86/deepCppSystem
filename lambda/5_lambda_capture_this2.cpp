/**
 * @file 5_lambda_capture_this2.cpp
 * @brief Value capture: 以值捕获 this 指针[*this]，相当于[pt = *this], 实际是对this指针进行了深拷贝
 * @author Albert
 * @version 1.0
 * @date 2025-01-03
 */

#include <iostream>
#include <vector>

using namespace std;

// struct lambda{
//     Point this;

//     void operator ()(){
//             this->x++;
//             this->y++;

//     };

// };

class Point
{
public:
    double x;
    double y;

    void print() const
    {
        std::cout << x << ", " << y << endl;
        ;
    }

    auto invoke()
    {
#ifdef USE_THIS
        auto lambda = [*this]() mutable {
            this->x++;
            this->y++;
            this->print();
        };
#else
        // value capture, this 指针被指捕获，相当于 [pt = *this] 对 this 对象进行了深拷贝
        auto lambda = [pt = *this]() mutable {
            pt.x++;
            pt.y++;
            pt.print();
        };
#endif
        return lambda;
    }
};

int main()
{
    // 属于同一个作用域
    {
        Point p1{ 100, 200 };
        auto lambda = p1.invoke(); // invoke(&p1);

        lambda();
        cout << sizeof(lambda) << endl;
        p1.print();
    }
}
