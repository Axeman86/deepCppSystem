/**
 * @file 1_stack_heap.cpp
 * @brief 堆和栈的区别
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-21
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int data;

class Point
{
public:
    int x{ 0 };
    int y{ 0 };

    void print() { cout << dec << x << "," << y << endl; }

    inline static int data = 100;
};

// int Point::data=100;

void process()
{
    const int len = 1000;
    //常量栈数组
    int myarray[len]; // alloca
}

void func()
{
    double data = 3.14;

    // Point pt{10,20};
    int x = 10;
    int y = 20;

    Point * p1 = new Point{ x, y }; /// new Point{x,y} 堆对象

    cout << hex << &x << ", " << &y << ", " << &p1 << endl;
    // Point* p2=new Point{x,y};

    delete p1;
    /// delete p2;
}

int main()
{
    func();

    {
        int x{ 10 };
        int arr[]  = { 1, 2, 3, 4, 5 }; //栈数组
        auto y     = 20;
        auto s1    = "hello"s; //自动类型推导 string
        int & data = x;        //栈引用
    }

    {
        int * px     = new int{ 10 };               //堆指针对象
        int * parray = new int[5]{ 1, 2, 3, 4, 5 }; //堆数组

        delete px;
        delete[] parray;
    }

    {
        vector<int> v{ 10, 20, 30, 40, 50 }; // vector use allocall dynamic application memory in heap

        for (auto & s : v)
        {
            cout << s << endl;
        }
    }

    {
        Point pt1{ 10, 20 };
        Point pt2{ 100, 200 };
        Point * p3 = new Point{ 10, 20 };
        Point * p4 = new Point{ 30, 40 };

        //内存的拷贝方向？
        pt1 = pt2; // 1. pt1.operator=(pt2)
        pt1.print();
        *p3 = *p4; // 2. p3->operator=(*p4)
        p3->print();
        pt2 = *p4; // 3. pt2.operator=(*p4)
        pt2.print();
        *p4 = pt1; // 4. p4->operator=(pt1)
        p4->print();

        Point & pr1 = *p3; //堆引用
        Point & pr2 = pt1; //栈引用

        Point * p5 = &pt1; //栈指针
        Point * p6 = &pr1; //堆指针

        cout << Point::data << endl;
        cout << p3->data << endl;

        delete p3;
        delete p4;
    }
}
