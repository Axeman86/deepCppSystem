/**
 * @file 4_predict_traits.cpp
 * @brief  使用 std::true_type 和 std::false_type 可以在编译时选择不同的类型或执行不同的操作;
 * @author Albert
 * @version 1.0
 * @date 2025-02-05
 */
#include <iostream>
#include <type_traits>

using namespace std;

// 通用版本默认继承自 false_type
template <typename T>
struct IsPointerT : std::false_type
{
};

// 特化版本继承自 true_type
template <typename T>
struct IsPointerT<T *> : std::true_type
{
    using BaseT = T;
};

// 通用版本默认形参为 false_type
template <typename T>
void invokeImpl(T, std::false_type)
{
    std::cout << "invokeImpl (T, false) " << endl;
}

// void invokeImpl(T, std::false_type)特化版本形参type为 int
template <>
void invokeImpl(int, std::false_type)
{
    std::cout << "invokeImpl (int, false) " << endl;
}

// 通用版本default argument is true_type
template <typename T>
void invokeImpl(T, std::true_type)
{
    std::cout << "invokeImpl (T, true) " << endl;
}

// void invokeImpl(T, std::true_type)特化版本形参type为 int*
template <>
void invokeImpl(int *, std::true_type)
{
    std::cout << "invokeImpl (int*, true) " << endl;
}

template <typename T>
void invoke(T t)
{
    invokeImpl(t, IsPointerT<T>{});
}

template <typename T>
void invoke_std(T t)
{
    invokeImpl(t, std::is_pointer<T>{});
}

int main(void)
{
    cout << "--------------------------------" << endl;
    {
        int data = 100;
        invoke(nullptr); // std::cout << "invokeImpl (T, false) "<<endl;
        invoke(data);    // std::cout << "invokeImpl (int, false) "<<endl;
        long * ptr{ nullptr };
        invoke(ptr); // std::cout << "invokeImpl (T, true) "<<endl;
        int * pdata = &data;
        invoke_std(pdata); // std::cout << "invokeImpl (int*, true) "<<endl;
    }
    return 0;
}
