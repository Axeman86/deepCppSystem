
#include <iostream>
#include <memory>
using namespace std;

class Widget
{
    int m_x;
    int m_y;
    int m_z;

public:
    Widget(int x, int y, int z) : m_x(x), m_y(y), m_z(z) { cout << "Widget ctor" << endl; }

    void print() { cout << m_x << "," << m_y << "," << m_z << endl; }

    ~Widget() { cout << "Widget dtor" << endl; }
};

class A
{
};

int main()
{
    cout << std::boolalpha;

    Widget * p = new Widget(1, 2, 3);

    unique_ptr<Widget> w1{ new Widget(1, 2, 3) };
    unique_ptr<Widget> w2 = make_unique<Widget>(1, 2, 3);

    w1->print();
    cout << sizeof(w1) << endl;

    cout << (w1 == nullptr) << endl;
    cout << (w2 == nullptr) << endl;

    // unique_ptr<Widget> w3=w1;
    unique_ptr<Widget> w3 = std::move(w1);
    /* w1->print(); */

    cout << (w1 == nullptr) << endl;
    cout << (w3 == nullptr) << endl;

    // w3=w2;
    w3 = std::move(w2);

    delete p;

    {
        unique_ptr<A> a1   = make_unique<A>();
        unique_ptr<int> a2 = make_unique<int>(10);
        cout << *a2 << endl;
        unique_ptr<int> a3 = make_unique<int>(20);
        cout << *a3 << endl;
    }
}

// template<class Tp, class... Args>
// inline  unique_ptr<Tp> make_unique(Args&&... args)
// {
//     return unique_ptr<Tp>(new Tp(std::forward<_Args>(args)...));
// }
