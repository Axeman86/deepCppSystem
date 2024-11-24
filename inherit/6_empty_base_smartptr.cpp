

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>

template <typename T>
struct DeleteByOperator
{
    void operator()(T * p) const { delete p; }
};

template <typename T>
struct DeleteByFree
{
    void operator()(T * p) const
    {
        p->~T();
        free(p);
    }
};

template <typename T>
struct DeleteDestructorOnly
{
    void operator()(T * p) const { p->~T(); }
};

template <typename DeletionPolicy>
class SmartPtr1
{ // 空基类优化
    DeletionPolicy deleter;
};

template <typename T>
class SmartPtr : private T
{ // 空基类优化
};

int main()
{
    std::cout << sizeof(DeleteByFree<int>) << std::endl;
    std::cout << sizeof(DeleteByFree<int>) << std::endl;
    std::cout << sizeof(DeleteDestructorOnly<int>) << std::endl;
    std::cout << sizeof(SmartPtr<DeleteDestructorOnly<int>>) << std::endl;
    std::cout << sizeof(SmartPtr1<DeleteDestructorOnly<int>>) << std::endl;
}
