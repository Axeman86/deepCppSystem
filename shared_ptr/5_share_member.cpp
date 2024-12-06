/**
 * @file 5_share_member.cpp
 * @brief 创建 ptr 的指针，与 r 共享所有权, 模版原型如下：
 *        template< typename T >
 *        shared_ptr( const shared_ptr<T>& r, element_type* ptr ) noexcept;
 *        shared_ptr<int> spd{spw, spw->data} 使用 spw 作为其控制块， 并指向 spw 所管理的 Widget 对象的 data 成员
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-01
 */
#include <iostream>
#include <memory>

using namespace std;

struct Widget
{
    double x;
    int * data;

    Widget() : data(nullptr) { cout << "Widget constructor" << endl; }
    ~Widget()
    {
        cout << "~Widget destructor" << endl;
        if (data != nullptr)
        {
            delete data;
            data = nullptr;
        }
    }
};

void process(Widget * w)
{
    cout << "is_pointer:" << boolalpha << is_pointer<decltype(w)>::value << endl;
    if (w->data)
        cout << "data:" << w->data << ", *data=" << *w->data << endl;
}

void process(int * data)
{
    cout << "is_pointer:" << boolalpha << is_pointer<decltype(data)>::value << endl;
    if (data)
        cout << "data:" << data << ", *data=> " << *data << endl;
}

int main()
{
    {
        Widget * w = new Widget();

        shared_ptr<Widget> spw1{ w };
        process(spw1.get());
        cout << sizeof(spw1) << endl;

        shared_ptr<Widget> spw2{ spw1 };
        process(spw1.get());
        cout << sizeof(spw2) << endl;
    }
    cout << "----------" << endl;
    {
        shared_ptr<Widget> spw(new Widget());

        cout << spw.use_count() << endl;
        spw->data = new int(20);

        cout << "shared_ptr<Widget> spw{new Widget()}" << endl;
        /* minimum number of 1Bytes, spw=0x557a37fd52e0 &spw->data=0x557a37fd52e8 spw->data=0x557a37fd5300 */
        cout << &spw << ":" << spw << ":" << &spw->data << ":" << spw->data << ":" << *spw->data << endl;

        // shared_ptr<int> spd{spw->data};  // error, no constructor
        // spd 是一个指向 Widget 对象的 data 成员的 shared_ptr，它依赖于 spw 的生命周期管理。
        shared_ptr<int> spd{
            spw, spw->data
        }; // spd 使用了 spw 作为其控制块（control block），并指向 spw 所管理的 Widget 对象的 data 成员

        cout << "after shared_ptr<int> spd{spw, spw->data}" << endl;
        cout << &spd << ":" << spd << ":" << *spd << endl;
        cout << spd.use_count() << endl;
        cout << spw.use_count() << endl;
        process(spw.get());
        process(spd.get());

        spw.reset();
        cout << "after reset..." << endl;
        cout << spd.use_count() << endl;
        cout << spw.use_count() << endl;

        process(spd.get());
    }
}
