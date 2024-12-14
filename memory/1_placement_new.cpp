/**
 * @file 1_placement_new.cpp
 * @brief 使用 placement new 在已分配的内存中构造对象; for malloc/free, operator new/delete
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-10
 */
#include <iostream>
#include <memory>

using namespace std;

class Point3d
{
private:
    int x;
    int y;
    int z;

public:
    Point3d(int x, int y, int z) : x(x), y(y), z(z) { cout << "ctor" << endl; }
    ~Point3d() { cout << "dtor" << endl; }
    Point3d(const Point3d &)             = default; // copy ctor
    Point3d(Point3d &&)                  = default; // move ctor
    Point3d & operator=(const Point3d &) = default;
    Point3d & operator=(Point3d &&)      = default; // move assignment

    virtual void print() { cout << x << " " << y << " " << z << endl; }
};

int main(int argc, char ** argv)
{
    cout << "sizeof(Point3d) = " << sizeof(Point3d) << endl;

    {
        cout << "-------use new / delete---------" << endl;
        Point3d * myObject = ::new Point3d{ 100, 200, 300 }; // operator new => placement new => callback constructor

        myObject->print();

        ::delete myObject; // call destructor, operator delete
    }

    {
        cout << "-------use malloc / free---------" << endl;
        void * memory = std::malloc(sizeof(Point3d));

        int * p1 = reinterpret_cast<int *>(memory);
        for (int i = 0; i < 6; i++)
        {
            cout << *p1 << " ";
            p1++;
        }
        cout << endl << "----------------------" << endl;

        Point3d * myObject = ::new (memory) Point3d{ 100, 200, 300 }; // operator new => placement new => callback constructor
                                                                      //
        myObject->print();

        long * p = reinterpret_cast<long *>(memory);
        cout << "memory address: " << p << ":" << *p << endl;
        p++;

        int * pi = reinterpret_cast<int *>(p);
        cout << *pi++ << endl;
        cout << *pi++ << endl;
        cout << *pi << endl;

        myObject->~Point3d(); // placement delete

        std::free(memory);
    }

    {
        cout << "-------use ::operator new / delete---------" << endl;
        // use ::operator new to allocate memory
        void * memory = ::operator new(sizeof(Point3d));
        // use placement new to construct object in memory
        Point3d * myObject = new (memory) Point3d{ 110, 220, 330 };

        myObject->print();
        myObject->~Point3d(); // placement delete

        ::operator delete(memory); // use ::operator delete to free memory, but not call destructor
    }

    return 0;
}
