/**
 * @file 2_smartptr-impl.cpp
 * @brief 智能指针实现
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-25
 */

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <utility>

using namespace std;

template <typename T>
class SmartPtr
{
public:
    explicit SmartPtr(T * p = nullptr) : p_(p) {}

    ~SmartPtr() { delete p_; }
    void release()
    {
        delete p_;
        p_ = nullptr;
    }

    T * operator->() { return p_; }
    const T * operator->() const { return p_; }

    T & operator*() { return *p_; }
    const T & operator*() const { return *p_; }

private:
    T * p_;
    SmartPtr(const SmartPtr &)             = delete;
    SmartPtr & operator=(const SmartPtr &) = delete;
};

class MyClass
{

public:
    MyClass() { cout << "MyClass 初始化" << endl; }

    ~MyClass() { cout << "MyClass 析构" << endl; }
};

/*
template <typename T, typename DeletionPolicy = DeleteByOperator<T>>
class SmartPtr : private DeletionPolicy {
public:
        explicit SmartPtr(T* p = nullptr,
        DeletionPolicy&& deletion_policy = DeletionPolicy()) : 	DeletionPolicy(std::move(deletion_policy)),p_(p)
        {}
        ~SmartPtr() {
                DeletionPolicy::operator()(p_);
        }
        void release() { p_ = NULL; }
    T* operator->() { return p_; }
    const T* operator->() const { return p_; }
    T& operator*() { return *p_; }
    const T& operator*() const { return *p_; }
    private:
    T* p_;
    SmartPtr(const SmartPtr&) = delete;
    SmartPtr& operator=(const SmartPtr&) = delete;
};*/

int main()
{
    SmartPtr p(new MyClass());
}
