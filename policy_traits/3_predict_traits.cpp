/**
 * @file 3_predict_trait.cpp
 * @brief std::false_type 和 std::true_type 的实现原理, 并且可以在编译时选择不同的类型或执行不同的操作;
 * @author Albert
 * @version 1.0
 * @date 2025-02-05
 */
#include <iostream>

using namespace std;

// 模拟 std::false_type 和 std::true_type 的实现
template <bool val>
struct BoolConstant
{
    using Type                  = BoolConstant<val>;
    static constexpr bool value = val;
};

using TrueType  = BoolConstant<true>;
using FalseType = BoolConstant<false>;

// 通用版本默认为 false, 两个类型不同
template <typename T1, typename T2>
struct IsSameT : FalseType
{
};

// 特化版本为 true, 两个类型相同
template <typename T>
struct IsSameT<T, T> : TrueType
{
};

// 通用版本默认形参为 TrueType
template <typename T>
void processImpl(T, TrueType)
{
    std::cout << "processImpl (T,true)" << endl;
}

// 通用版本默认形参为 FalseType
template <typename T>
void processImpl(T, FalseType)
{
    std::cout << "processImpl (T,false) " << endl;
}

// If T is int, then call IsSameT<int, int> and pass TrueType
// If T is not int, then call IsSameT<int, T> and pass FalseType
template <typename T>
void process(T t)
{
    processImpl(t, IsSameT<T, int>{});
}

// ---------------------------------------------------------------------
// 定义一个模板结构体，用于检查类型是否为指针类型
template <typename T>
struct IsPointer : FalseType
{
};

template <typename T>
struct IsPointer<T *> : TrueType
{
};

int main()
{
    {
        process(42);
        process(7.7);
    }

    std::cout << std::boolalpha;
    std::cout << "IsPointer<int>::value: " << IsPointer<int>::value << std::endl;
    std::cout << "IsPointer<int*>::value: " << IsPointer<int *>::value << std::endl;
}
