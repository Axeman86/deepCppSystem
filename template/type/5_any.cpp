/**
 * @file 5_any.cpp
 * @brief std::any 可以存储任何支持拷贝构造函数的类型，包括自定义类型
 *        std::any 使用的是小对象优化的内存模型，小对象存储在栈上，大对象存储在堆上，并使用RAII机制管理内存
 *        注意：尽量避免使用std::any, 特别是存储基本类型，因为会有额外的内存分配和释放，有缓存折损
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-30
 */
#include <any>
#include <iostream>

using namespace std;

int alloc_times   = 0;
int dealloc_times = 0;
int allocated     = 0;

void * operator new(size_t size)
{
    void * p = std::malloc(size);
    allocated += size;
    alloc_times++;
    return p;
}

void operator delete(void * p) noexcept
{
    dealloc_times++;
    return std::free(p);
}

void * operator new[](size_t size)
{
    void * p = std::malloc(size);
    allocated += size;
    alloc_times++;

    return p;
}
void operator delete[](void * p) noexcept
{
    dealloc_times++;
    return std::free(p);
}

struct Widget
{
    double x{};
    double z{};
    double u{};
    double v{};
    double w{};

    Widget() {}
    // Widget(const Widget& w)
    // {
    //     cout<<"copy ctor"<<endl;
    // }

    // Widget(Widget&& w)
    // {
    //     cout<<"move ctor"<<endl;
    // }

    ~Widget() { cout << "dtor" << endl; }
};

int main()
{
    cout << "总分配：" << allocated << " bytes, 分配次数：" << alloc_times << " 释放次数：" << dealloc_times << endl;

    {
        Widget w;

        std::any any1 = 100;
        try
        {
            // 使用 std::any_cast 将 std::any 转换为具体的类型
            auto i = any_cast<double>(any1);
            cout << "value is " << i << endl;
        } catch (const std::bad_any_cast & e)
        {
            cout << e.what() << endl;
        }
        cout << "总分配：" << allocated << " bytes, 分配次数：" << alloc_times << " 释放次数：" << dealloc_times << endl;
        std::any any2 = "hello"s;
        cout << "总分配：" << allocated << " bytes, 分配次数：" << alloc_times << " 释放次数：" << dealloc_times << endl;
        std::any any3 = w;
        cout << "总分配：" << allocated << " bytes, 分配次数：" << alloc_times << " 释放次数：" << dealloc_times << endl;

        cout << sizeof(std::any) << endl;
        cout << sizeof(any1) << endl;
        cout << sizeof(any2) << endl;
        cout << sizeof(any3) << endl;
        cout << sizeof(w) << endl;
        cout << (any3.type() == typeid(Widget)) << endl;
    }

    cout << "总分配：" << allocated << " bytes, 分配次数：" << alloc_times << " 释放次数：" << dealloc_times << endl;
}
