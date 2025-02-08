/**
 * @file 5_type_traits.cpp
 * @brief std::is_copy_constructible, std::is_move_constructible, std::is_copy_assignable, std::is_move_assignable 的使用方法
 *        类型判断的 traits , 对 std::false_type and std::true_type 实际使用;
 * @author Albert
 * @version 1.0
 * @date 2025-02-05
 */
#include <iostream>
#include <memory>
using namespace std;

class MyClass
{
public:
    MyClass() {}

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
};

class Point
{
    int m_x;
    int m_y;

public:
    Point(int x, int y) : m_x(x), m_y(y) {}
};

class Widget
{
    MyClass mc;
    Point * data;
    int value;

public:
    Widget(int _value = 0, int _x = 0, int _y = 0) : value(_value), data(new Point(_x, _y)) { cout << "ctor" << endl; }

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
        cout << "Widget copy ctor" << endl;
    }

    Widget(Widget && rhs) noexcept : mc(std::move(rhs.mc)), data(rhs.data), value(rhs.value)
    {

        rhs.data = nullptr; // 2. 将源对象的值设为有效状态
        cout << "Widget move ctor" << endl;
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

        cout << "copy assignment" << endl;
        return *this;
    }

    ~Widget()
    {
        delete data;
        cout << "dtor" << endl;
    }
};

int main()
{
    cout << boolalpha << endl;

    // 判断是否可以拷贝构造，则需要满足拷贝构造函数的存在性
    // => __is_constructible_impl<_Tp, const _Tp&>
    // => __is_constructible_impl<MyClass, const MyClass&>
    // => __is_constructible<MyClass, const MyClass&>
    cout << is_copy_constructible<MyClass>::value << '\n'; // true
    cout << is_copy_constructible_v<MyClass> << '\n';      // true
    cout << is_move_constructible_v<MyClass> << "\n";      // true
    cout << is_copy_assignable_v<MyClass> << '\n';         // true
    cout << is_move_assignable_v<MyClass> << '\n';         // true

    // unique_ptr is not copy constructible
    cout << is_copy_constructible_v<unique_ptr<MyClass>> << '\n'; // false
    cout << is_move_constructible_v<unique_ptr<MyClass>> << "\n"; // true
    // unique_ptr is not copy assignable
    cout << is_copy_assignable_v<unique_ptr<MyClass>> << '\n'; // false
    cout << is_move_assignable_v<unique_ptr<MyClass>> << '\n'; // true
}
