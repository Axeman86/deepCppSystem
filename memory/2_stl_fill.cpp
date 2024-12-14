/**
 * @file 2_stl_fill.cpp
 * @brief 使用 std::uninitialized_fill_n 在已分配的未初始化的内存中构造对象;
 *        使用 std::destroy_n 销毁多个对象，而不是销毁单个对象;
 *        使用 std::destroy_at 销毁单个对象，而不是销毁多个对象;
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-10
 */
#include <iostream>
#include <memory>
using namespace std;

class Point
{
public:
    Point(int x, int y, int z) : x(x), y(y), z(z) { cout << "ctor" << endl; }

    Point(const Point & obj)
    {
        cout << "copy ctor" << endl;
        this->x = obj.x;
        this->y = obj.y;
        this->z = obj.z;
    }
    Point & operator=(const Point & obj)
    {
        cout << "copy assignment" << endl;
        this->x = obj.x;
        this->y = obj.y;
        this->z = obj.z;
        return *this;
    }
    Point(Point && obj)
    {
        cout << "move ctor" << endl;
        Point p(std::move(obj));
        swap(this->x, p.x);
        swap(this->y, p.y);
        swap(this->z, p.z);
    }
    Point & operator=(Point && obj)
    {
        cout << "move assignment" << endl;
        Point p(std::move(obj));
        swap(this->x, p.x);
        swap(this->y, p.y);
        swap(this->z, p.z);
        return *this;
    }

    ~Point() { cout << "dtor" << endl; }

    void print() { cout << x << " " << y << " " << z << endl; }

    int x;
    int y;
    int z;
};

int main()
{
    {
        // application heap memory of uninitialized
        void * memory    = malloc(3 * sizeof(Point));
        Point * myObject = reinterpret_cast<Point *>(memory);

        Point myPoint{ 100, 200, 300 };
        myPoint.print();

        std::uninitialized_fill_n(myObject, 3, Point{ 110, 220, 330 });
        myObject[0].print();
        myObject[1].print();
        myObject[2].print();
        cout << "----" << endl;

        // 销毁多个对象，而不是释放内存
        std::destroy_n(myObject, 3);

        free(memory);
        cout << "---game over---" << endl;
    }

    {
        alignas(Point) char * memory[sizeof(Point) * 3]; // Allocate raw memory
        Point * myObject = reinterpret_cast<Point *>(memory);

        // 在未初始化的应用堆内存上构造对象
        Point * myPoint = new (myObject) Point{ 100, 200, 300 };
        myPoint->print();

        // 只是用于销毁 myObject 地址上的单个对象，而不是销毁 myObject 本身或多个对象
        destroy_at(myObject);
        cout << "---game over, again---" << endl;
    }
}
