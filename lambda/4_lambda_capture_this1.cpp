/**
 * @file 4_lambda_capture_this1.cpp
 * @brief [this]: 实际是以传值的方式捕获 this 指针，效果等同于传引用捕获
 * @author Albert
 * @version 1.0
 * @date 2025-01-03
 */

#include <iostream>
#include <vector>

using namespace std;

// struct lambda{
//     Point* this;

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
        // reference capture, 实际是以传值的方式捕获this指针，效果等同于传引用捕获
        auto lambda = [this]() {
            x++; // this->x++;
            this->y++;
        };
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
