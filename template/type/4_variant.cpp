/**
 * @file 4_variant.cpp
 * @brief variant<T> 使用模版参数，来存储多个强类型参数中的一个，
 *        测试验证对比 union 类型的使用方式和相应的RAII机制是否触发
 *        基本类型使用 union; 自定义类型使用 std::variant;
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-27
 */
#include <iostream>
#include <variant>

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

struct WidgetA
{
    double x{};
    WidgetA() { cout << "default ctor" << endl; }
    WidgetA(const WidgetA & w) { cout << "copy ctor" << endl; }

    WidgetA & operator=(const WidgetA & w)
    {
        cout << "copy assignment" << endl;
        return *this;
    }

    WidgetA(WidgetA && w) { cout << "move ctor" << endl; }

    ~WidgetA() { cout << "default dtor" << endl; }
};

struct WidgetB
{
    double x{};
    double y{};
};
struct WidgetC
{
    double x{};
    double y{};
    double z{};
    double u{};
    double v{};
    double w{};
};

union WidgetABCU
{
    WidgetA a;
    WidgetB b;
    WidgetC c;

    WidgetABCU() { cout << "WidgetABCU() ctor" << endl; }
    ~WidgetABCU() { cout << "~WidgetABCU() dtor" << endl; }
};

int main()
{
    // 自定义类型 WidgeABC，可以存储三个强类型 WidgeA/WidgeB/WidgeC
    using WidgetABC = std::variant<WidgetA, WidgetB, WidgetC>;

    cout << "std::variant : -----------" << endl;
    {
        WidgetABC w1 = WidgetA{};
        cout << "------------" << endl;
        WidgetABC w2 = w1;
        cout << "sizeof(WidgetABC) : " << sizeof(w1) << endl;
        cout << "sizeof(WidgetA)   : " << sizeof(WidgetA) << endl;
        cout << "sizeof(WidgetB)   : " << sizeof(WidgetB) << endl;
        cout << "sizeof(WidgetC)   : " << sizeof(WidgetC) << endl;
    }

    cout << "union : -----------" << endl; // union 不支持RAII, 移动、拷贝构造、析构
    {
        WidgetABCU w3;
        cout << sizeof(w3) << endl;
        WidgetA a;
        w3.a = a;

        // 不会主动的去trigger destructor, 只会在作用域结束时触发自己的析构函数 ~WidgetABCU()
        // w3.a.~WidgetA();
    }

    cout << "总分配：" << allocated << " bytes, 分配次数：" << alloc_times << " 释放次数：" << dealloc_times << endl;
}
