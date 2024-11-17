/**
 * @file 12_move_rvo.cpp
 * @brief 具名RVO和非具名RVO优化测试用例
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-17
 */
#include <iostream>
#include <vector>
using namespace std;

#define NO_MOVE
struct Point
{
    int x;
    int y;
    Point(int _x, int _y) : x(_x), y(_y) { }
};

struct Widget
{
    int value;
    Point * data;

    Widget(int _value = 0, int _x = 0, int _y = 0) : value(_value), data(new Point(_x, _y)) { cout << "ctor" << endl; }

    //   Widget(const Widget& rhs)=delete;
    //     Widget& operator=(const Widget& rhs)=delete;
    //     Widget(Widget&& rhs) noexcept=delete;
    //     Widget& operator=(Widget&& rhs) noexcept=delete;

    Widget(const Widget & rhs) : value(rhs.value), data(new Point(*rhs.data)) { cout << "copy ctor" << endl; }

    Widget(Widget && rhs) noexcept : value(rhs.value), data(rhs.data) // 1. 窃取源对象的指针值
    {
        rhs.data = nullptr; // 2. 将源对象的值设为有效状态
        cout << "move ctor" << endl;
    }

#ifdef NO_MOVE

    Widget & operator=(Widget && rhs) noexcept
    {
        if (this == &rhs)
        {
            return *this;
        }

        value = rhs.value;

        delete this->data;   // 1. 删除当前值
        data     = rhs.data; // 2. 窃取源对象的值
        rhs.data = nullptr;  // 3. 将源对象的值设为有效状态

        cout << "move assignment" << endl;
        return *this;
    }
#else
    Widget & operator=(const Widget & rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        Widget temp(rhs);
        swap(value, temp.value);
        swap(data, temp.data);

        cout << "copy assignment" << endl;
        return *this;
    }

    Widget & operator=(Widget && rhs) noexcept
    {
        if (this == &rhs)
        {
            return *this;
        }

        Widget temp(std::move(rhs));
        调用移动构造
        swap(value, temp.value);
        swap(data, temp.data);

        cout << "move assignment" << endl;
        return *this;
    }
#endif
    ~Widget()
    {
        cout << "dtor :" << data << endl;
        delete data;
    }

    void process()
    {
        cout << value << ": [" << data->x << "," << data->y << "]" << endl;
    }
};

#define USE_RVO
// 具名返回值优化
Widget createWidget_RVO()
{
    Widget w(10, 20);
#ifdef USE_RVO
    /* output:
     * ctor
     * */
    return w; // 交给编译器优化，if has copy assignment and move assignment operator，编译器会优化掉拷贝构造->RVO => return
              // Widget(10, 20);
#else
    /* output:
     * ctor
     * move ctor
     * dtor :0
     * */
    return std::move(w); // 编译器优化选项, if Widget not move construct, use copy constructor
#endif
}

// 非具名返回值优化
Widget createWidget_NRVO()
{
    return Widget(10, 20); // C++17 及以上标准要求 做拷贝消除--返回值优化
}

int main()
{
    {
        Widget w1 = createWidget_RVO(); // 返回值优化 > 移动构造 > 拷贝构造
    }

    cout << "-------" << endl;

    {
        Widget w1 = createWidget_NRVO(); // createWidget_NRVO
    }
}
