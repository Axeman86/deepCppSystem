/**
 * @file 4_class_new_delete.cpp
 * @brief 重载局部 new 和 delete 操作符，统计内存分配和释放次数;
 *        ::operator new(size) and ::operator delete(p) 只是分配和释放内存，不调用构造和析构函数;
 *        与 new 和 delete 不同, new 和 delete 会调用构造和析构函数;
 *        ::operator new: 是 C++ 的内存分配运算符，返回类型为 void*， 但通常与构造函数一起使用来创建对象。
 *        支持类型安全，可以直接用于对象的创建和初始化。
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-11
 */
#include <iostream>
using namespace std;

// void* T::operator new  ( std::size_t count );
// void* T::operator new[]( std::size_t count );

class MyClass
{
public:
    MyClass(const string & s) : _s(s) { cout << "ctor" << endl; }
    MyClass() { cout << "ctor" << endl; }
    ~MyClass() { cout << "dtor" << endl; }
    void process() { cout << _s << endl; }

    void * operator new(size_t size)
    {
        cout << "class new " << endl;

        data++;
        // ::operator new(size) 会调用全局的 operator new; :: 代表全局作用域, 只分配内存，不调用构造函数
        return ::operator new(size);
    }
    void operator delete(void * p)
    {
        cout << "class delete " << endl;
        // ::operator delete(p) 会调用全局的 operator delete; :: 代表全局作用域, 只释放内存，不调用析构函数
        ::operator delete(p);

        data--;
    }

    static int data;
    static int getData() { return data; }

private:
    string _s;
};

int MyClass::data = 0;

int main()
{
    // call class new and delete for MyClass::new and MyClass::delete
    MyClass * myObject = new MyClass{ "Software" };
    myObject->process();
    cout << "data = " << MyClass::getData() << endl;
    delete myObject;
    cout << "data = " << MyClass::getData() << endl;

    cout << "-----------" << endl;
    // call global new and delete for ::new and ::delete
    MyClass * p = ::new MyClass{};
    cout << "data = " << MyClass::getData() << endl;
    ::delete p;
}
