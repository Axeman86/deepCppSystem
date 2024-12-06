/**
 * @file 12_this_share_impl.cpp
 * @brief enable_shared_from_this 实现原理: 通过 weak_ptr 转 shared_ptr 实现 shared_from_this() 函数；
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-06
 */
#include <iostream>
#include <memory>

using namespace std;

template <typename T>
struct help_shared_from_this
{
    weak_ptr<T> weak_this;

    weak_ptr<T> weak_from_this() { return weak_this; }

    shared_ptr<T> shared_from_this()
    {
        cout << "shared_from_this " << is_convertible<weak_ptr<T>, shared_ptr<T>>::value << endl;
        if (!weak_this.expired())
        {
            return weak_this.lock();
        }
        else
        {
            throw exception{};
        }
    }
};

class Widget;
class Widget : public help_shared_from_this<Widget>
{
public:
    std::shared_ptr<Widget> getWidget() { return shared_from_this(); }

    void print() { cout << "print" << endl; }

    ~Widget() { cout << "~Widget()" << endl; }
};

int main()
{
    {
        shared_ptr<Widget> sp1 = make_shared<Widget>();
        sp1->weak_this         = sp1;

        shared_ptr<Widget> sp2 = sp1->getWidget(); //  sp2=sp1

        cout << "ref count: " << sp1.use_count() << endl;
        cout << "ref count: " << sp2.use_count() << endl;
    }
}

template <typename T>
class enable_shared_from_this
{
private:
    weak_ptr<T> weak_this;

public:
    // 调用时将weak_ptr转为shared_ptr
    shared_ptr<T> shared_from_this() { return shared_ptr<T>(weak_this); }

    shared_ptr<const T> shared_from_this() const { return shared_ptr<const T>(weak_this); }

    template <class U>
    friend class shared_ptr;
};

/* template <class T>
 * class shared_ptr
 * {
 *     shared_ptr
 *     {
 *         // 如果 T 可以转换为enable_shared_from_this<T> , 使用is_convertible判断
 *         // 则将 weak_this 指向一个shared_ptr<T>(this);
 *     }
 * };
 * */
