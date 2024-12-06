/**
 * @file 11_this_share_design_1.cpp
 * @brief shared_from_this() 使用, 通过 this 指针获取 shared_ptr 对象;
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-04
 */
#include <iostream>
#include <memory>

using namespace std;

class Widget;

void process(shared_ptr<Widget> tp);

// 1. 必须公有继承，确保Widget可转型为enable_shared_from_this
// 2. 必须使用shared_ptr指针，调用 shared_from_this()
//   安全做法：将构造函数private禁止创建栈对象、使用静态工厂函数确保创建shared_ptr指针
class Widget : public enable_shared_from_this<Widget>
{
public:
    int data;

    shared_ptr<Widget> getWidget()
    {
        return shared_from_this(); //正确      //shared_ptr<Widget>(this);错误！
    }

    void invoke()
    {
        process(shared_from_this()); // process(shared_ptr<Widget>(this));错误！
    }

    void print() { cout << "print" << endl; }

    ~Widget() { cout << "~Widget()" << endl; }

    Widget() = default;
};

void process(shared_ptr<Widget> tp)
{
    tp->print();
    cout << "ref count: " << tp.use_count() << endl;
    cout << "process end..." << endl;
}

int main()
{
    {
        shared_ptr<Widget> sp1{ new Widget() };
        shared_ptr<Widget> sp2 = sp1->getWidget(); //  sp2=sp1

        process(sp1);
        cout << "ref count: " << sp1.use_count() << endl;
        cout << "ref count: " << sp2.use_count() << endl;
    }
    cout << "--------" << endl;
    {
        try
        {
            Widget * p1            = new Widget();
            shared_ptr<Widget> sp2 = p1->getWidget(); //  裸指针调用抛异常 bad_weak_ptr
            cout << "ref count: " << sp2.use_count() << endl;
            delete p1;
        } catch (bad_weak_ptr & e)
        {
            cout << e.what() << endl;
        }
    }
    cout << "--------" << endl;
    {
        try
        {
            Widget w;

            shared_ptr<Widget> sp2 = w.getWidget(); //  栈对象调用抛异常 bad_weak_ptr
            cout << "ref count: " << sp2.use_count() << endl;
        } catch (bad_weak_ptr & e)
        {
            cout << e.what() << endl;
        }
    }
}

#if 0
// enable_shared_from_this() class 实现
template <class T>
class enable_shared_from_this
{
    weak_ptr<T> weak_this;

public:
    // 如果普通构造，weak_this为nullptr
    // 如果 公有继承、并且使用shared_ptr构造， weak_this 指向一个shared_ptr<T>(this);
    enable_shared_from_this() {}

    // 调用时将weak_ptr转为shared_ptr
    shared_ptr<T> shared_from_this() { return shared_ptr<T>(weak_this); }

    shared_ptr<const T> shared_from_this() const { return shared_ptr<const T>(weak_this); }

    template <class U>
    friend class shared_ptr;
};
#endif
