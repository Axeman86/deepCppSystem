/**
 * @file 14_ref_collapse.cpp
 * @brief 验证 & 左值引用具有传染性测试用例
 *          & &   --> &
 *          & &&  --> &
 *          && &  --> &
 *          && && --> &&
 *        如果传递的是一个左值，模板参数 T 会被推导为左值引用类型: T && 会折叠为 T &
 *        如果传递的是一个右值，模板参数 T 会被推导为非引用类型: T && 会折叠为 T
 * @author Albert
 * @version 1.0.0
 * @date 2024-10-26
 */
#include <iostream>
using namespace std;

class Widget
{
};

Widget getWidget()
{
    Widget w;
    return w;
}

template <typename T>
void invoke(T && obj)
{
    // 因为变量 obj 有地址，所以 obj 永远都会是左值

    cout << "is_lvalue_reference<decltype(obj)>::value:" << is_lvalue_reference<decltype(obj)>::value << endl; // Widget&
    cout << "is_lvalue_reference<T>::value:" << is_lvalue_reference<T>::value << endl;                         // Widget&
    cout << "is_lvalue_reference<T &&>::value:" << is_lvalue_reference<T &&>::value << endl;
    cout << "is_lvalue_reference<T &>::value:" << is_lvalue_reference<T &>::value << endl; // 永远左值 Widget& &

    cout << endl;

    cout << "is_rvalue_reference<decltype(obj)>::value:" << is_rvalue_reference<decltype(obj)>::value << endl;
    cout << "is_rvalue_reference<T>::value:" << is_rvalue_reference<T>::value << endl;
    cout << "is_lvalue_reference<T &&>::value: " << is_lvalue_reference<T &&>::value << endl;
    cout << "is_rvalue_reference<T &>::value:" << is_rvalue_reference<T &>::value << endl; // 永远左值
}

int main()
{
    cout << std::boolalpha;

    Widget w;
    invoke(w); // w: Widget&   ->  invoke(Widget& && obj) --> invoke(Widget& obj) : T is Widget &
    cout << "-------" << endl;

    invoke(getWidget()); // getWidget(): std::move(w): Widget&& -> invoke(Widget&& && obj) --> invoke(Widget&& obj) : T is Widge
    cout << "-------" << endl;

    {
        auto w1    = w;  // w1: Widget
        auto & w2  = w;  // w2: Widget&
        auto && w3 = w2; // Wdiget&& & -> Widget& , 指向左值引用的右值引用
        // auto& & w4=w; ERROR 没有引用的引用

        cout << is_lvalue_reference<decltype(w)>::value << endl;
        cout << is_lvalue_reference<decltype(w1)>::value << endl;
        cout << is_lvalue_reference<decltype(w2)>::value << endl;
        cout << is_lvalue_reference<decltype(w3)>::value << endl;

        cout << endl;

        cout << is_rvalue_reference<decltype(w)>::value << endl;
        cout << is_rvalue_reference<decltype(w1)>::value << endl;
        cout << is_rvalue_reference<decltype(w2)>::value << endl;
        cout << is_rvalue_reference<decltype(w3)>::value << endl;
    }

    cout << "-------" << endl;
    {
        auto w1         = getWidget(); // Widget
        const auto & w2 = getWidget(); // Widget & && -> Widget &
        auto && w3      = getWidget(); // Widget && && -> Widge &&
        invoke(w3);

        cout << is_lvalue_reference<decltype(w)>::value << endl;
        cout << is_lvalue_reference<decltype(w1)>::value << endl;
        cout << is_lvalue_reference<decltype(w2)>::value << endl;
        cout << is_lvalue_reference<decltype(w3)>::value << endl;

        cout << endl;

        cout << is_rvalue_reference<decltype(w)>::value << endl;
        cout << is_rvalue_reference<decltype(w1)>::value << endl;
        cout << is_rvalue_reference<decltype(w2)>::value << endl;
        cout << is_rvalue_reference<decltype(w3)>::value << endl;
    }
}
