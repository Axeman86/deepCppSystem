/**
 * @file 3_unique_memory.cpp
 * @brief unique_ptr的使用方法，以及自定义删除器的使用方法
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-25
 */

#include <iostream>
#include <memory>
using namespace std;

class Widget
{
    int m_x;
    int m_y;
    int m_z;

public:
    Widget(int x, int y, int z) : m_x(x), m_y(y), m_z(z) {}

    void print() { cout << m_x << ", " << m_y << ", " << m_z << endl; }

    ~Widget() { cout << "Widget dtor" << endl; }
};

// function object
struct DeleteFunctor
{
    // double data;
    void operator()(Widget * w)
    {
        delete w;
        cout << "------ DeleteFunctor delete w" << endl;
    }
};

void deleteFunction(Widget * w)
{
    delete w;
    cout << "------ deleteFunction delete w" << endl;
}

using FPointer = void (*)(Widget *);

int main()
{

    {
        cout << "------ default delete" << endl;
        Widget * p = new Widget{ 1, 2, 3 };
        unique_ptr<Widget> w1(new Widget(1, 2, 3));

        w1->print();
        cout << sizeof(w1) << endl;
        delete p;
    }

    {
        cout << "------ function object" << endl;
        DeleteFunctor dw;
        cout << sizeof(dw) << endl; // 1
        unique_ptr<Widget, DeleteFunctor> w2(new Widget(10, 20, 30));
        w2->print();
        cout << sizeof(w2) << endl;
    }

    {
        cout << "------ function pointer" << endl;
        unique_ptr<Widget, FPointer> w3(new Widget(1000, 2000, 3000), deleteFunction);
        w3->print();
        cout << sizeof(w3) << endl;
    }

    {
        cout << "------ lambda" << endl;
        auto lambda = [](Widget * w) {
            delete w;
            // closehandle(w);
            cout << "------ lambda delete w" << endl;
        };

        unique_ptr<Widget, decltype(lambda)> w4(new Widget(100, 200, 300), lambda);
        w4->print();
        cout << sizeof(w4) << endl;
    }

    {
        cout << "------ lambda capture" << endl;
        int data1 = 1, data2 = 2, data3 = 3;
        auto lambda = [=](Widget * w) {
            cout << data1 << data2 << data3 << endl;
            delete w;
            cout << "------ lambda delete w" << endl;
        };
        unique_ptr<Widget, decltype(lambda)> w5(new Widget(100, 200, 300), lambda);
        w5->print();
        cout << sizeof(w5) << endl; // 8+ 4+4+4=20 => 24
    }
}
