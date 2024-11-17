#include <iostream>
#include <vector>
using namespace std;

struct Point
{
    int x;
    int y;
};

struct Widget
{
    int value;
    Point * data;

    Widget(int _value = 0, int _x = 0, int _y = 0) : value(_value), data(new Point{ _x, _y }) { cout << "ctor" << endl; }

    Widget(const Widget & rhs) : value(rhs.value), data(new Point(*rhs.data)) { cout << "copy ctor" << endl; }

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

    ~Widget()
    {
        cout << "dtor :" << data << endl;
        delete data;
    }

    Widget(Widget && rhs) noexcept : value(rhs.value), data(rhs.data) // 1. 窃取源对象的指针值
    {
        rhs.data = nullptr; // 2. 将源对象的值设为有效状态
        cout << "move ctor" << endl;
    }

    Widget & operator=(Widget && rhs) noexcept
    {
        if (this == &rhs)
        {
            return *this;
        }
/* #define __USE_COPY_AND_SWAP */
#ifdef __USE_COPY_AND_SWAP
        value = rhs.value;

        delete data;         // 1. 删除当前值
        data     = rhs.data; // 2. 窃取源对象的值
        rhs.data = nullptr;  // 3. 将源对象的值设为有效状态
#else
        Widget tmp{ std::move(rhs) };
        cout << "Before------pointer data:" << tmp.data << " :" << data << endl;
        swap(value, tmp.value);
        swap(data, tmp.data);
        cout << "After------pointer data:" << tmp.data << " :" << data << endl;
#endif

        cout << "move assignment" << endl;
        return *this;
    }

    void process() { cout << value << ": [" << data->x << "," << data->y << "]" << endl; }
};

Widget createWidget()
{
    Widget w(1, 10, 20);
    return w;

    // return std::move(w); //不需要！适得其反！ 交给编译器自己去做优化
}

void invoke(Widget && w)
{
    cout << "invoke(Widget && w)..." << endl;
}

void invoke(const Widget & w)
{
    cout << "invoke(const Widget & w)..." << endl;
}

int main()
{
    {
        Widget w1(1, 10, 20);
        Widget w2(2, 100, 200);

        cout << "-----" << w1.data << "," << w2.data << endl;
        w2 = std::move(w1); //移动赋值 调用之后，w1不可用
        w2.process();
        // 如果使用内联对象，则不会有问题，因为只是进行了拷贝；
        // 使用了分离内存，所以会导致错误, 因为此分离内存的指针已经被移动;
        // w1.process();
        cout << "w1.value:" << w1.value << ", v2.value:" << w2.value << endl;
        cout << "-----" << w1.data << "," << w2.data << endl;
    }

    cout << "------" << endl;
    {
        const Widget w4{ 3, 1000, 2000 }; /// const Lvalue only use const&
        Widget w5{ 5, 1000, 2000 };
        w5 = std::move(w4);
    }

    cout << "------" << endl;
    {
        Widget w3 = createWidget(); // 1. 返回值优化 > 2. 移动 > 3. 拷贝
        invoke(w3);
    }

    cout << "------" << endl;
    {
        invoke(createWidget());
    }

    cout << "------" << endl;
    {
        invoke(createWidget());
    }

    // int data1=100;
    // int data2=std::move(data1);//int data2=data1;

    // Widget *w1=new Widget();
    // Widget* w2=new Widget();
    // w1=std::move(w2); // w1=w2;
}
