/**
 * @file 15_ref_not_forward.cpp
 * @brief 只有函数模版才能转发引用的测试用例
 * @author Albert
 * @version 1.0.0
 * @date 2024-10-26
 */
#include <iostream>
using namespace std;

template <typename T>
class Vector
{
public:
    void process1(T && obj) // 不是转发引用, 支持 Rvalue reference
    {
        cout << is_rvalue_reference<decltype(obj)>::value << endl;
    }

    template <typename U>
    void process2(U && obj)
    {
        cout << is_rvalue_reference<decltype(obj)>::value << endl;
    }
};

// 如果传递的是一个左值，模板参数 T 会被推导为左值引用类型: T && 会折叠为 T &
// 如果传递的是一个右值，模板参数 T 会被推导为非引用类型: T && 会折叠为 T
template <typename T>
void process(T && obj) //转发引用
{
    cout << "Is rvalue reference:" << is_rvalue_reference<decltype(obj)>::value << endl;
    cout << "Is lvalue reference:" << is_lvalue_reference<decltype(obj)>::value << endl;
}

int main()
{
    cout << std::boolalpha;
    string s = "forward";

    process("hello"s);
    process(s);
    cout << "---------" << endl;

    auto && obj2 = "hello"s; // obj2: string&&, 但是 obj2 是一个左值引用的右值引用, 因为 obj2 有地址
    process(obj2);

    Vector<string> v;
    v.process1("hello"s);
    // v.process1(s);   // ERROR , Argument is not pair, only rvalue reference

    v.process2("hello"s);
    v.process2(s);
}
