/**
 * @file 1_template_class.cpp
 * @brief C++模版是一种编译时机制，在编译时生成具体的代码；
 *        模版实例化是指编译器根据模版生成具体的类或函数，这个过程叫模版实例化；
 *        并且在实例化时，编译器会对实参类型进行检查，确保实参符合对模版参数的操作要求，如果实参类型不匹配，编译器会报错；
 *        模板类的成员函数定义在类外部，且显式实例化模板类的成员函数
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-14
 */
#include <array>
#include <iostream>
using namespace std;

template <typename T>
class Array
{
private:
    T * ptr;
    int size;

public:
    using value_type = T;
    using iterator   = value_type *;
    using reference  = value_type &;

    Array() {}
    Array(T arr[], int s);

    value_type * getPtr() { return ptr; }
    int getSize() { return size; }
    void print();
    virtual void show();
};

template <typename T>
Array<T>::Array(T arr[], int s)
{
    ptr  = new T[s];
    size = s;
    for (int i = 0; i < size; i++)
        ptr[i] = arr[i];
}

template <>
Array<int>::Array(int arr[], int s)
{
    cout << "特化构造函数" << endl;
    ptr  = new int[s];
    size = s;
    for (int i = 0; i < size; i++)
        ptr[i] = arr[i];
}

template <typename T>
void Array<T>::print()
{
    for (int i = 0; i < size; i++)
        cout << " " << *ptr + i;
    cout << endl;
}

template <typename T>
void Array<T>::show()
{
    for (int i = 0; i < size; i++)
        cout << " " << *(ptr + i);
    cout << endl;
}

template class Array<int>; // 显式实例化模板

int main()
{
    int arr[5] = { 1, 2, 3, 4, 5 };
    Array<int> a(arr, 5);
    a.print();
    a.show();
    cout << "---------" << endl;

    Array<int>::iterator begin; // int* begin;
    Array<int>::iterator end;
    for (begin = a.getPtr(), end = a.getPtr() + a.getSize(); begin != end; begin++)
    {
        cout << " " << *begin;
    }
    cout << endl;
}
