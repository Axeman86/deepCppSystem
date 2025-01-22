/**
 * @file 18_invoke_internal.cpp
 * @brief std::invoke 的内部实现原理, 自定义 myInvoke 函数，实现 std::invoke 的功能
 * @author Albert
 * @version 1.0
 * @date 2025-01-22
 */
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class MyClass
{
public:
    // std::invoke 无法正确解析重载的成员函数。你可以通过显式地指定成员函数指针来解决这个问题
    void print(int data) { cout << "MyClass print: " << data << endl; }
    void print(const std::string & prefix, int data) { cout << prefix << data << endl; }

    static void sprint(int data) { cout << "MyClass static sprint: " << data << endl; }
};

void print(int data)
{
    cout << "print function pointer: " << data << endl;
}

struct Printer
{
    void operator()(int data) const { cout << "Print Functor: " << data << endl; }
};

namespace MyCustom {
template <typename _Fp, typename _A0>
auto Invoke(_Fp && __f, _A0 && __a0)
{
    return __f(std::forward<_A0>(__a0));
}

/* member function called from myInvoke function: ned a object' this pointer, type can be a reference */
template <typename _Fn, typename _T1, typename _A0>
auto Invoke(_Fn && __f, _T1 & __t1, _A0 && __a0)
{
    return (__t1.*__f)(std::forward<_A0>(__a0));
}

/* member function called from myInvoke function: need a object' this pointer, type can be a pointer */
template <typename _Fn, typename _T1, typename _A0>
auto Invoke(_Fn && __f, _T1 * __t1, _A0 && __a0)
{
    return ((__t1)->*__f)(std::forward<_A0>(__a0));
}
} // namespace MyCustom

template <typename Iter, typename Callable, typename... Args>
void Foreach(Iter current, Iter end, Callable op, Args const &... args)
{
    while (current != end)
    {
        // cout << "*current: " << *current << endl;
        std::invoke(op, args..., *current);
        ++current;
    }
}

int main(void)
{
    MyClass mc;

    cout << "MyCustom::Invoke---------" << endl;
    {
        // auto myInvoke(_Fp && __f, _A0 && __a0)
        MyCustom::Invoke(print, 10);
        MyCustom::Invoke(Printer{}, 20);
        // ==> auto Invoke(_Fn && __f, _T1 * __t1, _A0 && __a0)
        MyCustom::Invoke(static_cast<void (MyClass::*)(int)>(&MyClass::print), &mc, 30);
        // ==> auto Invoke(_Fn && __f, _T1 & __t1, _A0 && __a0)
        MyCustom::Invoke(static_cast<void (MyClass::*)(int)>(&MyClass::print), mc, 30);
        // auto Invoke(_Fp && __f, _A0 && __a0)
        MyCustom::Invoke(&MyClass::sprint, 40);
        MyCustom::Invoke([](int data) { cout << "Lambda value:" << data << endl; }, 50);
    }

    cout << "std::Invoke---------" << endl;
    {
        std::invoke(print, 10);
        std::invoke(Printer{}, 20);
        std::invoke(static_cast<void (MyClass::*)(int)>(&MyClass::print), &mc, 30);
        std::invoke(static_cast<void (MyClass::*)(int)>(&MyClass::print), mc, 30);
        std::invoke(&MyClass::sprint, 40);
        std::invoke([](int data) { cout << "Lambda value:" << data << endl; }, 50);
    }

    cout << "std::invoke with for_each---------" << endl;
    {
        vector<int> v = { 1, 2, 3, 4, 5 };
        Foreach(v.begin(), v.end(), print);
        Foreach(v.begin(), v.end(), Printer{});
        Foreach(v.begin(), v.end(), static_cast<void (MyClass::*)(int)>(&MyClass::print), &mc);
        Foreach(v.begin(), v.end(), static_cast<void (MyClass::*)(const std::string &, int)>(&MyClass::print), &mc, "Prefix: ");
        Foreach(v.begin(), v.end(), &MyClass::sprint);
        Foreach(
            v.begin(), v.end(), [](const std::string prefix, int value) -> void { cout << prefix << value << endl; },
            "Lambda value: ");
    }
}
