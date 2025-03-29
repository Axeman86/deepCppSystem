/**
 * @file 12_pimpl.cpp
 * @brief Pimpl 是一种C++设计习语，用于隐藏类的实现细节，以减少编译依赖性。
 *        Pimpl 是一个缩写，意思是“Pointer to Implementation”，即指向实现的指针。
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-24
 */

#include <iostream>
#include <memory>

namespace MYCLASS {
// MyClass.h
// - 声明主类和实现类： 在头文件中声明主类，并使用前向声明声明实现类。
// - 在主类中使用指向实现类的指针：
// > - 在主类的私有成员中添加一个指向实现类的指针。
// > - 在主类的构造函数和析构函数中管理实现类的实例化和销毁。
class MyClassBaseImpl; // Forward declaration
class MyClass
{
public:
    MyClass();
    ~MyClass();
    void doSomething();
    void setImpl(std::unique_ptr<MyClassBaseImpl> impl) { mPimpl = std::move(impl); }

private:
    // 如果 MyClass 使用堆内存来管理其实现细节，并且使用智能指针
    // （如 std::unique_ptr）来管理这些资源，那么通常不需要实现深拷贝。
    // std::unique_ptr 本身已经提供了独占所有权语义，并且会在对象销毁时自动释放资源。
    std::unique_ptr<MyClassBaseImpl> mPimpl;
};

// MyClass.cpp
// - 在源文件中定义实现类。
// - 在实现类中实现具体功能：将所有实现细节放在实现类中。
class MyClassBaseImpl
{
public:
    MyClassBaseImpl()              = default;
    virtual ~MyClassBaseImpl()     = default;
    virtual void doSomethingImpl() = 0;
};
class MyClassImpl : public MyClassBaseImpl
{
public:
    MyClassImpl()  = default;
    ~MyClassImpl() = default;
    virtual void doSomethingImpl() override { std::cout << "Doing something in the implimentation class." << std::endl; }
};

class MyClassImpl1 : public MyClassImpl
{
public:
    MyClassImpl1()  = default;
    ~MyClassImpl1() = default;
    virtual void doSomethingImpl() override { std::cout << "Doing something in the implimentation 1 class." << std::endl; }
};

class myClassImpl2 : public MyClassImpl1
{
public:
    myClassImpl2()  = default;
    ~myClassImpl2() = default;
    virtual void doSomethingImpl() override { std::cout << "Doing something in the implimentation 2 class." << std::endl; }
};

MyClass::MyClass() : mPimpl(std::make_unique<MyClassImpl>()) {}
MyClass::~MyClass() = default;

void MyClass::doSomething()
{
    mPimpl->doSomethingImpl();
}

} // namespace MYCLASS

// main.cpp
using namespace MYCLASS;
int main()
{
    MyClass myClass;
    myClass.doSomething();
    // MyClass myClass2 = myClass; // copy constructor of 'MyClass' is implicitly deleted
    // because field 'mPimpl' has a deleted copy constructor
    myClass.setImpl(std::make_unique<MyClassImpl1>());
    myClass.doSomething();

    myClass.setImpl(std::make_unique<myClassImpl2>());
    myClass.doSomething();
    return 0;
}
