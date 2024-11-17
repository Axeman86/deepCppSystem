/**
 * @file 9_move_rules.cpp
 * @brief move&copy swap, move/copy 赋值操作符的实现，使用swap技术，减少内存分配和释放的次数，提高性能
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-17
 */
#include <iostream>
#include <vector>
using namespace std;

class MyClass
{
public:
    MyClass() { cout << "MyClass ctor" << endl; }

    MyClass(const MyClass & rhs) { cout << "MyClass copy ctor" << endl; }
    MyClass(MyClass && rhs) { cout << "MyClass move ctor" << endl; }

    MyClass & operator=(const MyClass & rhs)
    {
        cout << "MyClass copy assignment" << endl;
        return *this;
    }

    MyClass & operator=(MyClass && rhs)
    {
        cout << "MyClass move assignment" << endl;
        return *this;
    }

    ~MyClass() { cout << "MyClass dtor" << endl; }
};

class Point
{
    int m_x;
    int m_y;

public:
    Point(int x, int y) : m_x(x), m_y(y) { }
};

class Widget
{
    MyClass mc;
    Point * data;
    int value;

public:
    Widget(int x = 0, int y = 0) : data(new Point(x, y)) { cout << "Widget ctor:" << hex << data << endl; }
    Widget(const Widget & rhs) : value(rhs.value), mc(rhs.mc)
    {
        if (rhs.data != nullptr)
        {
            data = new Point(*rhs.data);
        }
        else
        {
            data = nullptr;
        }
        cout << "Widget copy ctor:" << hex << data << endl;
    }

    Widget(Widget && rhs) :
        // 1. 窃取源对象的指针值
        mc(std::move(rhs.mc)), // move ctor
        data(rhs.data), value(rhs.value)
    {

        rhs.data = nullptr; // 2. 将源对象的值设为有效状态
        cout << "Widget move ctor" << endl;
    }

    ~Widget()
    {
        cout << "Widget dtor:" << hex << data << endl;
        delete data;
    }

#ifdef NO_SWAP
    Widget & operator=(const Widget & rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        value = rhs.value;
        mc    = rhs.mc;

        if (rhs.data != nullptr)
        {
            if (data != nullptr)
            {
                *data = *rhs.data;
            }
            else
            {
                data = new Point(*rhs.data);
            }
        }
        else
        {
            delete data;
            data = nullptr;
        }

        cout << "Widget copy assignment" << endl;
        return *this;
    }

    Widget & operator=(Widget && rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        value = rhs.value;
        mc    = std::move(rhs.mc); // move assignment

        delete this->data;   // 1. 删除当前值
        data     = rhs.data; // 2. 窃取源对象的值
        rhs.data = nullptr;  // 3. 将源对象的值设为有效状态

        cout << "Widget move assignment" << endl;
        return *this;
    }
#else

    Widget & operator=(const Widget & rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        cout << "...Widget temp object creating" << endl;
        Widget tmp { rhs };
        cout << "...Widget temp object finish" << endl;

        swap(value, tmp.value);
        swap(data, tmp.data);
        cout << "...MyClass swap operating" << endl;
        swap(mc, tmp.mc);
        cout << "...MyClass swap operator finish" << endl;

        cout << "Widget copy assignment" << endl;
        return *this;
    }

    Widget & operator=(Widget && rhs) noexcept
    {
        if (this == &rhs)
        {
            return *this;
        }

        cout << "...Widget temp object creating" << endl;
        Widget temp(std::move(rhs)); // 调用移动构造
        cout << "...Widget temp object finish" << endl;
        swap(value, temp.value);
        swap(data, temp.data);
        cout << "...MyClass swap operating" << endl;
        swap(mc, temp.mc);
        cout << "...MyClass swap operator finish" << endl;

        cout << "Widget move assignment" << endl;
        return *this;
    }
#endif
};

class BigClass
{
    Widget w;
    vector<int> v;
    string text;
    int data;

public:
    BigClass() { cout << "BigClass ctor" << endl; }

    BigClass(const BigClass & rhs)             = default;
    BigClass & operator=(const BigClass & rhs) = default;
    BigClass(BigClass && rhs)                  = default;
    BigClass & operator=(BigClass && rhs)      = default;

    ~BigClass() { cout << "BigClass dtor" << endl; }
};

BigClass createBig()
{
    BigClass bc;
    cout << "BigClass constructor finish" << endl;
    return bc;
}

int main()
{
    {
        BigClass bc1 = createBig(); // 返回值优化 RVO
    }
    cout << "----" << endl;
    {

        BigClass bc1;
        cout << "BigClass constructor finish" << endl;
        bc1 = createBig(); //移动赋值, called move assignment
    }

    cout << "----" << endl;
    {
        BigClass bc1;
        BigClass bc2(std::move(bc1)); //移动构造
    }
    cout << "----" << endl;
    {
        BigClass bc1;
        BigClass bc2;

        bc1 = std::move(bc2); // 移动赋值, called move assignment
    }
    cout << "----" << endl;
    {
        BigClass bc1;
        const BigClass bc2;
        bc1 = std::move(bc2); // 强制移动赋值, last called copy assignment
    }
}
