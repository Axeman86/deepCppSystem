/**
 * @file 6_cast_share.cpp
 * @brief shared_ptr 的类型转换
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-03
 */
#include <iostream>
#include <memory>
using namespace std;

class Base
{
public:
    int a;
    virtual void process() { std::cout << "Base.process()" << endl; }
    virtual ~Base() { cout << "~Base" << endl; }
};

class Sub : public Base
{
public:
    void process() override { std::cout << "Sub.process()" << endl; }

    void invoke() { std::cout << "Sub.invoke()" << endl; }
    ~Sub() { cout << "~Sub" << endl; }
};

int main()
{
    {
        Base * b1 = new Base();
        Sub * s1  = new Sub();

        Base * b2 = s1;
        b2->process();

        Sub * s3 = dynamic_cast<Sub *>(b2);
        s3->process();

        delete b1;
        delete b2; //虚析构，多态删除
    }
    cout << "--------" << endl;

    {
        shared_ptr<Base> sp1{ new Base() };
        shared_ptr<Sub> sp2{ new Sub() };

        shared_ptr<Base> sp3{ sp2 };
        cout << sp3.use_count() << endl;

        // shared_ptr<Base> sp4{ sp2.get()}; //错误！
        /* shared_ptr<Base> sp4 = sp2; */ // right, 赋值兼容性原则

        // 1.先对原生指针static_cast
        // 2.再拷贝构造一个目标指针的shared_ptr
        shared_ptr<Base> sp4 = static_pointer_cast<Base>(sp2);
        cout << sp4.use_count() << endl;

        // shared_ptr<Sub> sp5{ dynamic_cast<Sub *>(sp4.get()) }; // ERROR, 非共享控制块，会导致 sp5 对 sp4.get() 这个内存进行
        // delete shared_ptr<Sub> sp5{ sp4, dynamic_cast<Sub *>(sp4.get()) };  // OK, sp5 与 sp4 共享控制块，内存不会重复释放
        shared_ptr<Sub> sp5 = std::dynamic_pointer_cast<Sub>(sp4); // OK, 使用强制类型转换进行赋值
        cout << sp5.use_count() << endl;
    }
}

#if 0
template <typename T>
class shared_ptr
{
    template <class Y>
    explicit shared_ptr(Y * ptr);
};

template <typename T, typename DeleteType = defaultDelete>
class unique_ptr
{
    explicit unique_ptr(T * ptr);
};

template <class T, class U>
std::shared_ptr<T> static_pointer_cast(const std::shared_ptr<U> & r) noexcept
{
    auto p = static_cast<typename std::shared_ptr<T>::element_type *>(r.get());
    return std::shared_ptr<T>{ r, p };
}

template <class T, class U>
std::shared_ptr<T> dynamic_pointer_cast(const std::shared_ptr<U> & r) noexcept
{
    if (auto p = dynamic_cast<typename std::shared_ptr<T>::element_type *>(r.get()))
    {
        return std::shared_ptr<T>{ r, p };
    }
    else
    {
        return std::shared_ptr<T>{};
    }
}
#endif
