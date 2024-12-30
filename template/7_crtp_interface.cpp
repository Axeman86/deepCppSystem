/**
 * @file 7_crtp_interface.cpp
 * @brief 奇异递归模板模式（Curiously Recurring Template Pattern, CRTP）是一种在C++中使用模板的编程技巧。
 *        它允许一个类将自己作为模板参数传递给基类，从而实现静态多态性(即:编译时多态性)。
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-22
 */
#include <iostream>

using namespace std;

// 总结：通过这种方式，Base 类可以调用派生类的实现，而不需要使用虚函数，从而实现了静态多态性
// 1. Base 类是一个模板类，它接受一个派生类 Derived 作为模板参数。
template <typename T>
class Base
{
public:
    // 2. Base 类定义了一个 interface 方法，该方法调用派生类的 implementation 方法
    void interface()
    {
        // 调用派生类的实现
        static_cast<T *>(this)->implementation();
    }

    // 基类提供的默认实现
    void implementation()
    {
        // 默认行为
        std::cout << "Base implementation" << std::endl;
    }
};

// 3. Derived 类继承自 Base<Derived>，并提供了自己的 implementation 方法
class Derived : public Base<Derived>
{
public:
    void implementation()
    {
        // 派生类的具体实现
        std::cout << "Derived implementation" << std::endl;
    }
};

// 4. Derived 类继承自 Base<Derived>，没有提供了自己的 implementation 方法
class Derived2 : public Base<Derived2>
{
    // 没有提供implementation，所以使用基类的默认实现
};

int main()
{
    Derived d;
    d.interface(); // 输出 "Derived implementation"

    Derived2 d2;
    d2.interface(); // 输出 "Base implementation"
    return 0;
}
