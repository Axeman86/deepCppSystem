/**
 * @file 12_this_share_design_2.cpp
 * @brief shared_from_this() 使用, 通过 this 指针获取 shared_ptr 对象; 创建静态工厂函数来创建 shared_ptr 对象；
 *        禁止创建栈对象；禁止创建裸指针；禁止使用 this 指针创建 shared_ptr 对象；
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-06
 */
#include <iostream>
#include <memory>

using namespace std;

class Widget;

void process(shared_ptr<Widget> tp);

// 1. 必须公有继承，确保Widget可转型为enable_shared_from_this
// 2. 必须使用shared_ptr指针，调用 shared_from_this()
// 3. 安全做法：将构造函数private禁止创建栈对象、使用静态工厂函数确保创建shared_ptr指针
// - 通过禁用拷贝构造函数、拷贝赋值运算符、移动构造函数和移动赋值运算符，可以确保 Widget 对象只能通过 shared_ptr 创建和管理，
// - 避免潜在的错误和内存管理问题。这是一个良好的实践，特别是在使用 std::enable_shared_from_this 的情况下。
class Widget : public enable_shared_from_this<Widget>
{
public:
    int data;

    shared_ptr<Widget> getWidget()
    {

        return shared_from_this(); // 正确
        // shared_ptr<Widget>(this);错误！

        // 以下代码等价, 但是不推荐
        // weak_ptr<Widget> weak_this = weak_from_this();
        //
        // if (!weak_this.expired())
        // {
        //     return shared_from_this(); // 替换 shared_ptr<Widget>{weak_this};
        // }
        // else
        // {
        //     cout << "oops, expired..." << endl;
        //     return shared_ptr<Widget>{ nullptr };
        // }
    }

    void invoke()
    {
        process(shared_from_this()); // ERROR: process(shared_ptr<Widget>(this));
    }

    void print() { cout << "print..." << endl; }

    ~Widget() { cout << "~Widget()" << endl; }
    // 禁用拷贝构造函数和拷贝赋值运算符
    Widget(const Widget &)             = delete;
    Widget & operator=(const Widget &) = delete;

    // 禁用移动构造函数和移动赋值运算符
    Widget(Widget &&)             = delete;
    Widget & operator=(Widget &&) = delete;

    // 工厂函数
    static shared_ptr<Widget> create() { return shared_ptr<Widget>(new Widget()); }

private:
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
    shared_ptr<Widget> sp3;
    if (sp3)
    {
        cout << "sp3 is not nullptr" << endl;
    }
    else
    {
        cout << "sp3 is nullptr" << endl;
    }

    {
        shared_ptr<Widget> sp1 = Widget::create();
        shared_ptr<Widget> sp2 = sp1->getWidget(); //  sp2=sp1

        process(sp1);
        cout << "ref count: " << sp1.use_count() << endl;
        cout << "ref count: " << sp2.use_count() << endl;

        cout << "is_convertible<Widget *, enable_shared_from_this<Widget> *>::value is " << boolalpha;
        cout << is_convertible<Widget *, enable_shared_from_this<Widget> *>::value << endl;
    }

    {
        // cout << "--------" << endl;
        // Widget * p1 = new Widget(); // ERROR: 不能创建裸指针
        // shared_ptr<Widget> sp2 = p1->getWidget(); //  裸指针调用抛异常 bad_weak_ptr
        // cout<<"ref count: "<<sp2.use_count()<<endl;
        // delete p1;
    }

    {
        // cout << "--------" << endl;
        // Widget w;  // ERROR: 不能创建栈对象
        // shared_ptr<Widget> sp2 = w.getWidget(); //  栈对象调用抛异常 bad_weak_ptr
        // cout<<"ref count: "<<sp2.use_count()<<endl;
    }
}

#if 0
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
