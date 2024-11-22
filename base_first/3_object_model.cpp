/**
 * @file 3_object_model.cpp
 * @brief 内存对齐模型，长字段放前面，短字段放后面，使得内存对齐进行聚合
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-21
 */
#include <iostream>
#include <string>
using namespace std;

struct Point
{
    double x;
    double y;
};

class Rectangle1
{
    Point leftUp; //值语义
    int width;
    int height;
};

/*
class Rectangle1
{
    double x;
    double y;
    int width;
    int height;

};*/

class Rectangle2
{
    Point * m_leftUp; //堆指针, 栈指针?

    int m_width;
    int m_height;

public:
    Rectangle2(double x, double y, int width, int height) : m_leftUp(new Point{ x, y }), m_width(width), m_height(height) {}

    ~Rectangle2() { delete m_leftUp; }
};

class Rectangle3
{
    Point & leftUp; //引用——很少见
    int width;
    int height;
};

class MyShape
{
    Rectangle1 r1; // 24 byte
    Rectangle2 r2; // 16 byte
    Point p;       // 16 byte
    int x;         // 4 byte
    int y;         // 4 byte
    int * data;    // 8 byte
};

int main()
{

    Rectangle1 r1;

    Rectangle2 r2(10, 20, 100, 200);

    cout << sizeof(Point) << endl;
    cout << sizeof(Rectangle1) << endl;
    cout << sizeof(Rectangle2) << endl;
    cout << sizeof(Rectangle3) << endl;
    cout << sizeof(MyShape) << endl;
}
