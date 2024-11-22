/**
 * @file 7_raii.cpp
 * @brief RAII (Resource Acquisition Is Initialization) 资源获取即初始化
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-22
 */
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

#define RAII

template <typename T>
class SmartPtr
{
public:
    explicit SmartPtr(T * p = nullptr) : p_(p) {}

    ~SmartPtr() { delete p_; }
    void release()
    {
        delete p_;
        p_ = nullptr;
    }

    T * operator->() { return p_; }
    const T * operator->() const { return p_; }

    T & operator*() { return *p_; }
    const T & operator*() const { return *p_; }

private:
    T * p_;
    SmartPtr(const SmartPtr &)             = delete;
    SmartPtr & operator=(const SmartPtr &) = delete;
};

class MyClass
{
public:
    MyClass() { cout << "MyClass Initial" << endl; }

    ~MyClass() { cout << "MyClass Deinitial" << endl; }
    void doSomething() { cout << "doSomething" << endl; }
};

void process(int data)
{
    cout << "process start" << endl;

#ifndef RAII
    // 需要自己管理内存，手动释放内存
    MyClass * p = new MyClass();
#else
    /* 利用栈对象的生命周期，来对堆对象的内存管理释放 */
    SmartPtr p(new MyClass()); // nead -std=c++17/gnu++17 or higher; else use
                               // SmartPtr<MyClass> p(new MyClass());
#endif

    p->doSomething();
    if (data < 0)
    {
        invalid_argument exp("data");
        throw exp;
    }

    cout << "process end" << endl;
#ifndef RAII
    delete p;
#endif
}

void process1()
{
    unique_ptr<MyClass> p(new MyClass());
    p->doSomething();
}

int main()
{
    try
    {
        process(-100);
    } catch (invalid_argument & e)
    {
        cerr << "invalid arg: " << e.what() << endl;
    }

    process1();
}
