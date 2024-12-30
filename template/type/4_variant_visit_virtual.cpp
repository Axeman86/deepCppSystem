/**
 * @file 4_variant_visit_virtual.cpp
 * @brief variant<T> 机制配合 std::visit 实现多态访问的测试用例
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-30
 */
#include <iostream>
#include <variant>

using namespace std;

class Shape
{
public:
    virtual void draw() const = 0;
    /* virtual ~Shape() { cout << "~Shape dtor" << endl; }; */
    virtual ~Shape() = default;
};

class Circle : public Shape
{
public:
    void draw() const override { cout << "Circle draw()" << endl; }
    Circle() { cout << "Circle ctor" << endl; }
    ~Circle() { cout << "~Circle dtor" << endl; }
    Circle(const Circle & c) { cout << "Circle copy ctor" << endl; }
    Circle & operator=(const Circle & c)
    {
        cout << "Circle copy assignment" << endl;
        return *this;
    }
    Circle(Circle && c) { cout << "Circle move ctor" << endl; }
    Circle & operator=(Circle && c)
    {
        cout << "Circle move assignment" << endl;
        return *this;
    }
};

class Square : public Shape
{
public:
    void draw() const override { cout << "Square draw()" << endl; }
    Square() { cout << "Square ctor" << endl; }
    ~Square() { cout << "~Square dtor" << endl; };
    Square(const Square & s) { cout << "Square copy ctor" << endl; }
    Square & operator=(const Square & s)
    {
        cout << "Square copy assignment" << endl;
        return *this;
    }
    Square(Square && s) { cout << "Square move ctor" << endl; }
    Square & operator=(Square && s)
    {
        cout << "Square move assignment" << endl;
        return *this;
    }
};

class Triangle : public Shape
{
public:
    void draw() const override { cout << "Triangle draw()" << endl; }
    Triangle() { cout << "Triangle ctor" << endl; }
    ~Triangle() { cout << "~Triangle dtor" << endl; };
    Triangle(const Triangle & t) { cout << "Triangle copy ctor" << endl; }
    Triangle & operator=(const Triangle & t)
    {
        cout << "Triangle copy assignment" << endl;
        return *this;
    }
    Triangle(Triangle && t) { cout << "Triangle move ctor" << endl; }
    Triangle & operator=(Triangle && t)
    {
        cout << "Triangle move assignment" << endl;
        return *this;
    }
};

// Visitor 模式中的访问者类型
class ShapeVisitor
{
public:
    void operator()(const Circle & c)
    {
        cout << "Circle visitor" << endl;
        c.draw();
    }
    void operator()(const Square & s)
    {
        cout << "Square visitor" << endl;
        s.draw();
    }
    void operator()(const Triangle & t)
    {
        cout << "Triangle visitor" << endl;
        t.draw();
    }
    virtual ~ShapeVisitor() = default;
};

int main(int argc, char ** argv)
{
    using myVariant = std::variant<Circle, Square, Triangle>;

    myVariant v;
    cout << "-------if object v is not null, destroy before store object" << endl;
    v = Circle();
    cout << "====================" << endl;
    std::visit(ShapeVisitor(), v);

    cout << "-------if object v is not null, destroy before store object" << endl;
    v = Square();
    cout << "====================" << endl;
    std::visit(ShapeVisitor(), v);

    cout << "-------if object v is not null, destroy before store object" << endl;
    v = Triangle();
    cout << "====================" << endl;
    std::visit(ShapeVisitor(), v);

    cout << "Program Finish! free all memory and destroy objects" << endl;

    return 0;
}
