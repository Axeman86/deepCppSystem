/**
 * @file 11_binding.cpp
 * @brief Lvalues and Rvalues binding rules
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-17
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

void f1(Widget &)
{
    cout << "lvalue reference" << endl;
}
void f2(const Widget &)
{
    cout << "const lvalue reference" << endl;
}
void f3(Widget &&)
{
    cout << "rvalue reference" << endl;
}
void f4(const Widget &&)
{
    cout << "const rvalue reference" << endl;
}

const auto data = R"(
|         | &  | const & |  && | const && |
| Lvalue  | Y  |    Y    |  N  |     N    |
| CLvalue | N  |    Y    |  N  |     N    |
| Rvalue  | N  |    Y    |  Y  |     Y    |
| CRvalue | N  |    Y    |  N  |     Y    |
)";

int main()
{
    cout << data << endl;
    {
        Widget w1;
        f1(w1); // OK
        f2(w1); // OK
        // f3(w1); // ERROR!
        // f4(w1); // ERROR!
    }

    cout << "----------------" << endl;
    {
        const Widget w2;
        // f1(w2); // ERROR!
        f2(w2); // OK
        // f3(w2); // ERROR!
        // f4(w2); // ERROR!
    }

    cout << "----------------" << endl;
    {
        // f1(getWidget()); // ERROR!
        f2(getWidget()); // OK 延长了临时对象的生命周期
        f3(getWidget()); // OK
        f4(getWidget()); // OK
    }

    cout << "----------------" << endl;
    {
        // f1(static_cast<const Widget &&>(getWidget())); // ERROR!
        f2(static_cast<const Widget &&>(getWidget())); // OK
        // f3(static_cast<const Widget &&>(getWidget())); // ERROR!
        f4(static_cast<const Widget &&>(getWidget())); // OK
    }

    return 0;
}
