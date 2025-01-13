/**
 * @file 9_lambda_capture_move.cpp
 * @brief 移动捕获 unique_ptr<> 对象, 因为 unique_ptr<> 对象不能被拷贝
 * @author Albert
 * @version 1.0
 * @date 2025-01-04
 */
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Point
{
public:
    double x;
    double y;
    void print() const { std::cout << x << ", " << y << endl; }
};

int main()
{
    unique_ptr<Point> p = make_unique<Point>();

    // 移动捕获 unique_ptr<> 对象, 因为 unique_ptr<> 对象不能被拷贝
    auto lambda8 = [pt = std::move(p)]() {
        pt->x++;
        pt->y++;
        pt->print();
    };

    lambda8();
}
