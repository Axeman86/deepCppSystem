/**
 * @file 13_ref_forward.cpp
 * @brief 验证模版函数完美转发测试用例
 * @author Albert
 * @version 1.0.0
 * @date 2024-10-26
 */
#include <iostream>
using namespace std;

class Widget
{
public:
    Widget() {}
    Widget(const Widget & rhs) { cout << "copy ctor" << endl; }
    Widget(Widget && rhs) { cout << "move ctor" << endl; }
    Widget & operator=(Widget && rhs)
    {
        cout << "move assignment" << endl;
        return *this;
    }
    Widget & operator=(const Widget & rhs)
    {
        cout << "copy assignment" << endl;
        return *this;
    }
};

void process(Widget & param)
{
    cout << "process left value" << endl;
}
void process(Widget && param)
{
    cout << "process right value" << endl;
}

template <typename T>
void invoke(T && param)
{
    cout << "left or right? " << endl;
    process(std::forward<T>(param));
}

/*
 * 模版实例化的时候，会根据参数类型进行选择
 *
void invoke<Widget&> (Widget& param)
{
    cout<<"left or right? "<<endl;
    process(std::forward<Widget&>(param));
}
void invoke<Widget>(Widget&& param)
{
    cout<<"left or right? "<<endl;
    process(std::forward<Widget>(param));
}*/

int main()
{
    Widget w;

    invoke(w);
    invoke(std::move(w));
}

/*

//移除引用traits
template <class _Tp>
struct  remove_reference
{
    typedef  _Tp type;
};

template <class _Tp>
struct  remove_reference<_Tp&>
{
    typedef  _Tp type;
};

template <class _Tp>
struct  remove_reference<_Tp&&>
{
    typedef  _Tp type;
};


template <class _Tp>
inline constexpr _Tp&&
forward(typename remove_reference<_Tp>::type& __t) noexcept {
  return static_cast<_Tp&&>(__t);
}


template <class _Tp>
inline constexpr _Tp&&
forward(typename remove_reference<_Tp>::type&& __t) noexcept {
  static_assert(!is_lvalue_reference<_Tp>::value, "cannot forward an rvalue as an lvalue");
  return static_cast<_Tp&&>(__t);
}
*/
