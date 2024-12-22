/**
 * @file 5_template_special.cpp
 * @brief 模板特化: 为特定类型提供特定实现
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-16
 */
#include <iostream>
using namespace std;

template <typename T>
class Array
{
private:
    T * ptr;
    int size;

public:
    Array(T arr[], int s);
    void print();
};

template <typename T>
Array<T>::Array(T arr[], int s)
{
    ptr  = new T[s];
    size = s;
    for (int i = 0; i < size; i++)
        ptr[i] = arr[i];
}

template <typename T>
void Array<T>::print()
{
    for (int i = 0; i < size; i++)
    {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
}

template <> //表示特化版本
void Array<bool>::print()
{
    for (int i = 0; i < size; i++)
    {
        cout << boolalpha << *(ptr + i) << " : ";
    }
    cout << endl << "template special type boolalpha" << endl;
}

int main()
{
    int arr[5] = { 1, 2, 3, 4, 5 };
    Array<int> a1(arr, 5);
    a1.print();

    bool boo[5] = { true, false, true, false, true };
    Array<bool> a2(boo, 5);
    a2.print();
}
