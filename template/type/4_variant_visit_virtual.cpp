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
    void draw() const override { cout << "Circle" << endl; }
    ~Circle() { cout << "~Circle dtor" << endl; }
};

class Square : public Shape
{
public:
    void draw() const override { cout << "Square" << endl; }
    ~Square() { cout << "~Square dtor" << endl; };
};

class Triangle : public Shape
{
public:
    void draw() const override { cout << "Triangle" << endl; }
    ~Triangle() { cout << "~Triangle dtor" << endl; };
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
    cout << "-------" << endl;
    v = Circle();
    std::visit(ShapeVisitor(), v);

    cout << "-------if object v is not null, destroy before store object" << endl;
    v = Square();
    std::visit(ShapeVisitor(), v);

    cout << "-------if object v is not null, destroy before store object" << endl;
    v = Triangle();
    std::visit(ShapeVisitor(), v);

    cout << "Program Finish! free all memory and destroy objects" << endl;

    return 0;
}
