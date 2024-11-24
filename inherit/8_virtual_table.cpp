#include <iostream>

using namespace std;

class Base
{
public:
    size_t d1;
    virtual void M1() {}
    virtual ~Base() = default;
};

class Sub : public Base
{
public:
    size_t d2;
    void M1() override {}
    virtual void M2() {}
};

int main()
{
    cout << "Hello World" << endl;
    Base b;
    b.d1 = 10;

    Sub s;
    s.d1 = 100;
    s.d2 = 200;

    std::cout << "sizeof(b) = " << sizeof(b) << ", &b = 0x" << &b << endl; // 8+8=16
    cout << "sizeof(s) = " << sizeof(s) << ", &s = 0x" << &s << endl;      // 16+8=24

    size_t * p1 = reinterpret_cast<size_t *>(&b);
    cout << "p1 pointer parse 0x" << *p1 << ", p1->d1 = ";
    p1++;
    cout << *p1 << endl;

    size_t * p2 = reinterpret_cast<size_t *>(&s);
    cout << "p2 pointer parse 0x" << *p2 << ", p2->d1 = ";
    p2++;
    cout << *p2 << ", p2->d2 = ";
    p2++;
    cout << *p2 << endl;

    Base b1;
    cout << "sizeof(b1) = " << sizeof(b1) << ", &b1 = 0x" << &b1 << endl; // 8+8=16
    size_t * pvt1 = reinterpret_cast<size_t *>(&b1);
    cout << "Base class virtual table is equal:" << boolalpha << (*pvt1 == *reinterpret_cast<size_t *>(&b)) << ", " << pvt1
         << "->0x" << *pvt1 << ":0x" << *(reinterpret_cast<size_t *>(*pvt1)) << endl;
    Sub s1;
    cout << "sizeof(s1) = " << sizeof(s1) << ", &s1 = 0x" << &s1 << endl; // 16+8=24
    size_t * pvt2 = reinterpret_cast<size_t *>(&s1);
    cout << "Sub class virtual table is equal:" << boolalpha << (*pvt2 == *reinterpret_cast<size_t *>(&s)) << ", " << pvt2 << "->0x"
         << *pvt2 << ":0x" << *(reinterpret_cast<size_t *>(*pvt2)) << endl;
}
