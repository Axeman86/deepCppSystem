/**
 * @file 2_point_reference.cpp
 * @brief pointer and reference
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-21
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Point
{
    int x;
    int y;
};

void process1(const Point & p)
{
    // p.x++;
}

void process2(Point p) {}

void process3(Point * p) {}

Point process4()
{
    Point p{ 10, 20 };
    return p;
}

Point & process5()
{
    Point p{ 10, 20 };
    return p; //错误
}

Point * process6()
{

    Point * p = new Point{ 10, 20 };
    return p;
}

int main()
{
    func();

    Point * p = new Point{ 10, 20 };
    process3(p);
    delete p;

    Point p2;
    process1(p2);
    process1(*p);

    Point * p3 = process6();
    //...
    delete p3;
}
