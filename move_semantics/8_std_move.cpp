/**
 * @file 8_std_move.cpp
 * @brief std::move的实现，其本质是一种强制类型转换，即:右值类型转换；
 *        使用static_cast<T &&>(T)来实现move语义, 把其它类型转换为右值引用类型;
 *        move函数并不做具体的移动操作，其目的只是告诉编译器当前对象具备可移动条件;
 *        如果不能满足移动的条件，对移动构造函数的调用会被转换为拷贝构造函数的调用:
 *        1. 如果参数本身不支持移动语义
 *        2. 如果是对 const 左值参数调用 std::move，移动不接受 const 对象参数
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-17
 */
#include <iostream>

namespace myStdMove {

// Type Traits

// remove_reference<int>::type  -->  int
template <class T>
struct remove_reference
{
    using type = T;
};

// remove_reference<int&>::type  -->  int
template <class T>
struct remove_reference<T &>
{
    using type = T;
};

// remove_reference<int&&>::type  -->  int
template <class T>
struct remove_reference<T &&>
{
    using type = T;
};

template <typename _Tp>
constexpr typename remove_reference<_Tp>::type && move(_Tp && __t) noexcept
{
    std::cout << "myStdMove::move" << std::endl;
    return static_cast<typename remove_reference<_Tp>::type &&>(__t);
}

// std::move(T) == > static_cast<T &&>(T);
//
// Widget w1;
//
// std::move(w1) == > static_cast<Widget &&>(w1);

} // namespace myStdMove

class Widget final
{
public:
    Widget() { std::cout << "ctor" << std::endl; };
    ~Widget() = default;
    Widget(const Widget & rhs) { std::cout << "copy ctor" << std::endl; }
    Widget(Widget && rhs) { std::cout << "move ctor" << std::endl; }
    Widget & operator=(const Widget & rhs) noexcept
    {
        std::cout << "copy assignment" << std::endl;
        return *this;
    }
    Widget & operator=(Widget && rhs) noexcept
    {
        std::cout << "move assignment" << std::endl;
        return *this;
    }

    void operator()() { std::cout << "operator()" << std::endl; }
};

class MyClass
{
public:
    MyClass() { std::cout << "MyClass ctor" << std::endl; }
    MyClass(const MyClass & rhs) { std::cout << "MyClass copy ctor" << std::endl; }
    MyClass(MyClass && rhs) = delete;
    MyClass & operator=(const MyClass & rhs)
    {
        std::cout << "MyClass copy assignment" << std::endl;
        return *this;
    }
    MyClass & operator=(MyClass && rhs) = delete;
    ~MyClass() { std::cout << "MyClass dtor" << std::endl; }
};

int main(void)
{
    {
        Widget w1;
        Widget w2 = myStdMove::move(w1);
        w1();
    }

    std::cout << "======================" << std::endl;
    {
        myStdMove::move(MyClass());
    }

    std::cout << "======================" << std::endl;
    {
        Widget w1;
        Widget w2 = std::move(w1);
        w1();
    }

    return 0;
}
